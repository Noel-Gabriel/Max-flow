# python script used to generate the graphs to benchmark the different max flow algorithms
# using the python module pynetget based on the netget algorithm https://doi.org/10.1287/mnsc.20.5.814
import pynetgen as ng
import os

# help(ng.netgen_generate)


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
                       supply=1,                   # honestly no idea what this does, but needed to generate edges with maxcap and mincap
                       nodes=nodes,                # number of vertices
                       density=edges,              # number of edges
                       fname=curr_path+"/test graphs/" + file_name) # where to save the generated graph


generate(nodes=1000, edges=400000, max_capacity=10)