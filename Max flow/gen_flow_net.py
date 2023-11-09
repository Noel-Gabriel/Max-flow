# python script used to generate the graphs to benchmark the different max flow algorithms
# using the python module pynetget based on the netget algorithm https://doi.org/10.1287/mnsc.20.5.814
import pynetgen as ng
import os

# help(ng.netgen_generate)
def generate_gd(rows, columns, max_capacity, min_capacity=1):
    curr_path = os.path.dirname(__file__)
    file_name = "gd"+str(rows)+"x"+str(columns)+".dimacs"
    ng.grid_generate(seed=-1, 
                     rows=rows, 
                     columns=columns, 
                     skeleton=1, 
                     diagonal=1,
                     reverse=0, 
                     wrap=0, 
                     mincost=1, 
                     maxcost=1, 
                     supply=max_capacity,
                     capacitated=100, 
                     mincap=min_capacity, 
                     maxcap=max_capacity, 
                     rng=1,
                     markers=0, 
                     fname=curr_path+"/test graphs/"+file_name)


def generate(nodes, edges, max_capacity, min_capacity=1):
    curr_path = os.path.dirname(__file__)
    file_name = str(nodes)+"x"+str(edges)+".dimacs"
    ng.netgen_generate(seed=-1,                    # -1 -> random seed
                       mincost=1,                  # irrelevant, 1 needed to generate max flow problem
                       maxcost=1,                  # irrelevant, 1 needed to generate max flow problem
                       sources=1,                  # single source, 0 
                       sinks=1,                    # single sink, nodes-1
                       maxcap=max_capacity,        # max possible capacity on an edge
                       mincap=min_capacity,        # min possible capacity on an edge
                       supply=max_capacity,        # honestly no idea what this does, but needed to generate edges with maxcap and mincap
                       nodes=nodes,                # number of vertices
                       density=edges,              # number of edges
                       rng=1,                      # use the random number generator found in the python library random
                       fname=curr_path+"/test graphs/" + file_name) # where to save the generated graph


#generate(nodes=10, edges=50, max_capacity=1000)
#generate_gd(300,600,1000)
"""
generate(nodes=8214, edges=38813, max_capacity=1000)
generate(nodes=16807, edges=80262, max_capacity=1000)
generate(nodes=32768, edges=157696, max_capacity=1000)
generate(nodes=65025, edges=314840, max_capacity=1000)
"""
generate(nodes=2000, edges=9100, max_capacity=10000)