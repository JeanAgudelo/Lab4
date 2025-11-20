#include "Red.h"

Red::Red() {}

Red::~Red() {
    for (auto &it : enrutadores)
        delete it.second;
}

void Red::agregarEnrutador(string nombre) {
    if (!enrutadores.count(nombre)) {
        enrutadores[nombre] = new Enrutador(nombre);
        cout << "Enrutador " << nombre << " agregado.\n";
    } else {
        cout << "Enrutador " << nombre << " ya existe.\n";
    }
}

void Red::eliminarEnrutador(string nombre) {
    if (enrutadores.count(nombre)) {
        for (auto &it : enrutadores)
            if (it.first != nombre)
                it.second->eliminarVecino(nombre);

        delete enrutadores[nombre];
        enrutadores.erase(nombre);
        cout << "Enrutador " << nombre << " eliminado.\n";

        calcularRutas();
    } else {
        cout << "No existe enrutador " << nombre << "\n";
    }
}

void Red::agregarConexion(string origen, string destino, int costo) {
    if (!enrutadores.count(origen)) {
        cout << "No existe origen " << origen << "\n";
        return;
    }
    if (!enrutadores.count(destino)) {
        cout << "No existe destino " << destino << "\n";
        return;
    }

    enrutadores[origen]->agregarVecino(destino, costo);
    enrutadores[destino]->agregarVecino(origen, costo);
    cout << "Conexion agregada: " << origen << " - " << destino << " costo " << costo << "\n";
}

void Red::dijkstra(string origen) {
    if (!enrutadores.count(origen)) return;

    map<string, int> dist;
    map<string, string> prev;
    for (auto &p : enrutadores) {
        dist[p.first] = INF;
        prev[p.first] = "";
    }
    dist[origen] = 0;

    using P = pair<int, string>;
    // El comparador para min-heap (menor costo primero)
    auto cmp = [](const P &a, const P &b) { return a.first > b.first; };
    priority_queue<P, vector<P>, decltype(cmp)> pq(cmp);
    pq.push({0, origen});

    while (!pq.empty()) {
        auto cur = pq.top(); pq.pop();
        int d = cur.first;
        string u = cur.second;
        if (d > dist[u]) continue;

        for (auto &en : enrutadores[u]->getVecinos()) {
            string v = en.destino;
            int w = en.costo;
            if (dist[v] > (long long)dist[u] + w) { // Usar long long para evitar overflow
                dist[v] = dist[u] + w;
                prev[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    map<string, int> tablaCostos;
    map<string, vector<string>> tablaCaminos;
    for (auto &p : enrutadores) {
        string destino = p.first;
        tablaCostos[destino] = dist[destino];
        vector<string> path;

        // Solo calcular camino si es alcanzable
        if (dist[destino] < INF) {

            string cur = destino;
            while (cur != "" && cur != origen) {
                path.push_back(cur);
                cur = prev[cur];
            }
            // Agrega el origen al final después del bucle
            path.push_back(origen);

            // Si el camino se construye correctamente, debe tener al menos el origen y el destino.
            // Si el destino es el origen, path será solo [origen]
            // Si el destino es alcanzable, path será [destino, ..., origen]
            reverse(path.begin(), path.end());
            tablaCaminos[destino] = path;
        } else {
            // No alcanzable
            tablaCaminos[destino] = vector<string>();
        }
    }

    enrutadores[origen]->setTablaCostos(tablaCostos);
    enrutadores[origen]->setTablaCaminos(tablaCaminos);
}

void Red::calcularRutas() {
    for (auto &p : enrutadores) {
        dijkstra(p.first);
    }
    cout << "Rutas recalculadas.\n";
}

void Red::cargarDesdeArchivo(string nombreArchivo) {
    // Limpiar red existente
    for (auto &it : enrutadores)
        delete it.second;
    enrutadores.clear();

    ifstream f(nombreArchivo);
    if (!f.is_open()) {
        cout << "No se pudo abrir archivo: " << nombreArchivo << "\n";
        return;
    }

    string linea;
    int lineNo = 0;
    while (getline(f, linea)) {
        lineNo++;
        // trim (simple) y omitir comentarios
        if (linea.empty() || linea[0] == '#') continue;

        stringstream ss(linea);
        vector<string> tokens;
        string tk;
        while (ss >> tk) tokens.push_back(tk);
        if (tokens.empty()) continue;

        if (tokens.size() == 2 && (tokens[0] == "R" || tokens[0] == "r")) {
            agregarEnrutador(tokens[1]);
        } else if (tokens.size() == 3) {
            string o = tokens[0], d = tokens[1];
            int costo;
            try {
                // Verificar si los enrutadores existen antes de agregar la conexión.
                // Si no existen, las llamadas a agregarEnrutador() se encargarán de crearlos.
                if (!enrutadores.count(o)) agregarEnrutador(o);
                if (!enrutadores.count(d)) agregarEnrutador(d);

                costo = stoi(tokens[2]);
                agregarConexion(o, d, costo);

            } catch (...) {
                cout << "Linea " << lineNo << " formato invalido (costo no entero o enrutador no pudo crearse).\n";
            }
        } else {
            cout << "Linea " << lineNo << " ignorada (formato inesperado).\n";
        }
    }

    f.close();
    calcularRutas();
    cout << "Carga desde archivo finalizada.\n";
}

void Red::crearRedAleatoria(int numEnrutadores, int numConexiones) {
    if (numEnrutadores <= 0) return;

    // Limpiar red existente
    for (auto &it : enrutadores)
        delete it.second;
    enrutadores.clear();

    // crear enrutadores
    for (int i = 1; i <= numEnrutadores; ++i) {
        agregarEnrutador("R" + to_string(i));
    }

    // generar lista de pares posibles
    vector<pair<string,string>> posibles;
    vector<string> nombres;
    for (auto &p : enrutadores) nombres.push_back(p.first);

    for (size_t i = 0; i < nombres.size(); ++i) {
        for (size_t j = i+1; j < nombres.size(); ++j) {
            posibles.push_back({nombres[i], nombres[j]});
        }
    }

    // limitar conexiones al máximo posible
    int maxPosibles = (int)posibles.size();
    if (numConexiones > maxPosibles) numConexiones = maxPosibles;

    // mezclar aleatoriamente
    random_device rd;
    mt19937 g(rd());
    shuffle(posibles.begin(), posibles.end(), g);

    uniform_int_distribution<int> distCosto(1, 20);
    for (int i = 0; i < numConexiones; ++i) {
        string a = posibles[i].first;
        string b = posibles[i].second;
        int costo = distCosto(g);
        agregarConexion(a, b, costo);
    }

    calcularRutas();
    cout << "Red aleatoria creada (" << numEnrutadores << " routers, " << numConexiones << " conexiones).\n";
}

void Red::imprimirTodasLasTablas() {
    vector<string> todos;
    for (auto &p : enrutadores) todos.push_back(p.first);
    sort(todos.begin(), todos.end());

    cout << "\n---- Tablas de costos (filas = enrutador origen) ----\n";
    // imprimir encabezado
    cout << "Origen |";
    for (auto &n : todos) cout << "\t" << n;
    cout << "\n";

    for (auto &n : todos) {
        enrutadores[n]->imprimirTablaCostos(todos);
    }
}

void Red::imprimirTablaIndividual(string nombre) {
    if (!enrutadores.count(nombre)) {
        cout << "No existe enrutador " << nombre << "\n";
        return;
    }
    enrutadores[nombre]->imprimirTablaSimple();
}

void Red::imprimirCamino(string origen, string destino) {
    if (!enrutadores.count(origen)) {
        cout << "No existe enrutador origen " << origen << "\n";
        return;
    }
    if (!enrutadores.count(destino)) {
        cout << "No existe enrutador destino " << destino << "\n";
        return;
    }
    enrutadores[origen]->imprimirCamino(destino);
}
