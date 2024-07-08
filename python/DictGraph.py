# "Life is really simple, but we insist on making it complicated."
#  ~ Confucius
class DictGraph:
    def __init__(self, directed=False):
        """
        Unweighted graph structure implemented using a built-in python dict
        as underlying structure
        parameters: directed -> specifies if graph is bidirectional or not
        """
        self.nodes = {}
        self.directed = directed

    def __len__(self):
        return len(self.nodes)

    def add_node(self, name):
        """
        add node to the graph structure
        """
        self.nodes[name] = []

    def remove_node(self, node):
        """
        remove node from graph structure
        """
        del self.nodes[node]
        for key in self.nodes:
            if node in self.nodes[key]:
                idx = self.nodes[key].idx(node)
                return self.nodes[key].pop(idx)

    def add_edge(self, nodea, nodeb):
        """
        add edge to the graph structure
        """
        self.nodes[nodea].append(nodeb)
        if not self.directed:
            self.nodes[nodeb].append(nodea)

    def remove_edge(self, nodea, nodeb):
        """
        remove edge from graph
        """
        edge = None
        if nodeb in self.nodes[nodea]:
            idx = self.nodes[nodea].index(nodeb)
            edge = self.nodes[nodea].pop(idx)
        if not self.directed and edge is not None:
            self.nodes[nodeb].remove(nodea)
        return edge

    def yield_connections(self):
        """
        iterates through edges
        """
        for node in self.nodes:
            yield self.nodes[node]

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
        present = nodeb in self.nodes[nodea]
        if not self.directed:
            return present
        return present or nodea in self.nodes[nodeb]

    def adjacent(self, node):
        """
        returns list of adjacent (neighbouring nodes)
        """
        return self.nodes[node]

    def neighbours(self, node):
        """
        yields (generates iterable) of neighbouring nodes
        """
        for n in self.adjacent(node):
            yield n

    def outdegree(self, node):
        """
        return outgoing edge count
        """
        return len(self.nodes[node])

    def indegree(self, node):
        """
        return incoming edge count
        """
        count = 0
        for n in self.nodes:
            if node in self.nodes[n]:
                count += 1
        return count

    def degree(self, node):
        """
        return number of edges for node
        """
        if self.directed:
            return self.indegree(node) + self.outdegree(node)
        return self.outdegree(node)


class WeightedDictGraph(DictGraph):
    def __init__(self, directed=False):
        """
        Weighted graph data structure that uses pythons dict
        """
        super().__init__(directed)
        self.weights = {}

    def add_node(self, name):
        """
        add node to the graph
        """
        self.nodes[name] = {}

    def add_edge(self, nodea, nodeb, weight):
        """
        add connection (edge) between two points on
        the graph
        """
        self.nodes[nodea][nodeb] = weight
        if not self.directed:
            self.nodes[nodeb][nodea] = weight

    def remove_edge(self, nodea, nodeb):
        """
        remove edge from the graph
        """
        edge = None
        if nodea in self.nodes and nodeb in self.nodes[nodea]:
            edge = self.nodes[nodea][nodeb]
            del self.nodes[nodea][nodeb]
            if not self.directed:
                del self.nodes[nodeb][nodea]
        return edge
