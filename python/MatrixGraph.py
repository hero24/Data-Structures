# "Every moment is a fresh beginning."
# ~ T.S. Eliot

class MatrixGraph:
    def __init__(self, directed=False):
        """
        Unweighted graph structure implemented using a built-in python list
        as underlying matrix
        parameters: directed -> specifies if graph is bidirectional or not
        """
        self.nodes = []
        self.connections = []
        self.directed = directed

    def __len__(self):
        return len(self.nodes)

    def add_node(self, name):
        """
        add node to the graph structure
        """
        self.nodes.append(name)
        self.connections += [[False]]
        for connection in self.connections:
            length = len(self.nodes) - len(connection)
            connection += [False for _ in range(length)]

    def remove_node(self, node):
        """
        remove node from graph structure
        """
        idx = self.nodes.index(node)
        for connection in self.connections:
            connection.pop(idx)
        self.nodes.pop(idx)
        self.connections.pop(idx)

    def add_edge(self, nodea, nodeb):
        """
        add edge to the graph structure
        """
        nodea, nodeb = self._get_connection(nodea, nodeb)
        self.connections[nodea][nodeb] = True
        self.connections[nodeb][nodea] = not self.directed

    def remove_edge(self, nodea, nodeb):
        """
        remove edge from graph
        """
        nodea, nodeb = self._get_connection(nodea, nodeb)
        self.connections[nodea][nodeb] = False
        if not self.directed:
            self.connections[nodeb][nodea] = self.directed
        return nodea, nodeb

    def yield_connections(self):
        """
        iterates through edges
        """
        for connection in self.connections:
            yield connection

    def yield_nodes(self):
        """
        iterates through nodes
        """
        for node in self.nodes:
            yield node

    def order(self):
        """
        return number of nodes
        """
        return len(self.nodes)

    def has_node(self, node):
        """
        returns True if node exists in graph,
        False otherwise
        """
        return node in self.nodes

    def has_edge(self, nodea, nodeb):
        """
        returns True if edge exists
        """
        nodea, nodeb = self._get_connection(nodea, nodeb)
        present = self.connections[nodea][nodeb]
        if not self.directed:
            return present
        return present or self.connections[nodeb][nodea]

    def adjacent(self, node):
        """
        returns list of adjacent (neighbouring nodes)
        """
        return [node for node in self.neighbours(node)]

    def neighbours(self, node):
        """
        yields (generates iterable) of neighbouring nodes
        """
        idx = self.nodes.index(node)
        for i, connection in enumerate(self.connections):
            if connection[idx]:
                yield self.nodes[i]
        if self.directed:
            for i, connection in enumerate(self.connections[idx]):
                yield connection[i]

    def outdegree(self, node):
        """
        return outgoing edge count
        """
        node = self.nodes.index(node)
        return self.connections[node].count(True)

    def indegree(self, node):
        """
        return incoming edge count
        """
        node = self.nodes.index(node)
        count = 0
        for connection in self.connections:
            if connection[node]:
                count += 1
        return count

    def degree(self, node):
        """
        return number of edges for node
        """
        if self.directed:
            return self.indegree(node) + self.outdegree(node)
        return self.outdegree(node)

    def _get_connection(self, nodea, nodeb):
        nodea = self.nodes.index(nodea)
        nodeb = self.nodes.index(nodeb)
        return nodea, nodeb


class WeightedMatrixGraph(MatrixGraph):
    def __init__(self, directed=False):
        """
        Weighted matrix-based graph
        """
        super().__init__(directed)

    def add_edge(self, nodea, nodeb, weight):
        """
        add edge to the graph structure
        """
        nodea, nodeb = self._get_connection(nodea, nodeb)
        self.connections[nodea][nodeb] = weight
        if not self.directed:
            self.connections[nodeb][nodea] = weight

    def remove_edge(self, nodea, nodeb):
        """
        remove edge from graph
        returns weight, node a and node b
        """
        nodea, nodeb = self._get_connection(nodea, nodeb)
        weight = self.connections[nodea][nodeb]
        self.connections[nodea][nodeb] = False
        if not self.directed:
            self.connections[nodeb][nodea] = False
        return weight, nodea, nodeb

    def get_weight(self, nodea, nodeb):
        """
            returns weight of the edge
        """
        nodea, nodeb = self._get_connection(nodea, nodeb)
        weight = self.connections[nodea][nodeb]
        return weight
