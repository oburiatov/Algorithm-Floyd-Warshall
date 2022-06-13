from matplotlib import scale
import networkx as nx
import matplotlib.pyplot as plt

G = nx.DiGraph()
G.add_weighted_edges_from(
    [('A', 'B','30'),
    ('A', 'C','2'), 
    ('D', 'B','19'), 
    ('C', 'E','21'), 
    ('E', 'F','10'),
    ('B', 'H','84'), 
    ('B', 'G','45'), 
    ('B', 'F','1'), 
    ('C', 'G','4')]
    )
G.add_edge("A","B",)
# G.add_weighted_edges_from()

nx.set_edge_attributes(G, values = 300, name = 'weight')
val_map = {'A': 0.4,
           'F': 0.4
           }

values = [val_map.get(node, 0.3) for node in G.nodes()]

# Specify the edges you want herfe
red_edges = [('A', 'C'), ('C', 'E'), ('E','F')]

edge_colours = ['black' if not edge in red_edges else 'red'
                for edge in G.edges()]
black_edges = [edge for edge in G.edges() if edge not in red_edges]


pos = nx.spring_layout(G,k=1, iterations=20)
nx.draw_networkx_nodes(G, pos, cmap=plt.get_cmap('jet'), 
                       node_color = values, node_size = 500)
nx.draw_networkx_labels(G, pos,font_color="whitesmoke")
nx.draw_networkx_edges(G, pos, edgelist=red_edges, edge_color='r', arrows=True, width=2.0)
nx.draw_networkx_edges(G, pos, edgelist=black_edges, arrows=True)
nx.draw_networkx_edge_labels(G, pos, edge_labels = nx.get_edge_attributes(G,'weight'))
plt.show()