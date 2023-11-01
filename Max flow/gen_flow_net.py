# python script used to generate the graphs to benchmark the different max flow algorithms
# using the python module pynetget based on the netget algorithm https://doi.org/10.1287/mnsc.20.5.814
import pynetgen as ng

# help(ng.netgen_generate)

ng.netgen_generate(seed=-1,      # -1 = random seed
                   mincost=1,    # irrelevant, 1 needed to generate max flow problem
                   maxcost=1,    # irrelevant, 1 needed to generate max flow problem
                   sources=1,    # single source, 0 
                   sinks=1,      # single sink, nodes-1
                   maxcap=10000,    # max possible capacity on an edge
                   mincap=100,     # min possible capacity on an edge
                   supply=1,     # honestly no idea what this does, but needed to generate edges with maxcap and mincap
                   nodes=800,    # number of vertices
                   density=10000, # number of edges
                   fname="/Users/noel/Desktop/Max flow vscode/Max-flow/Max flow/test.dimacs") # where to save the generated graph