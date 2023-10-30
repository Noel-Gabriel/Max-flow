# python script used to generate the graphs to benchmark the different max flow algorithms
# using the python module pynetget based on the netget algorithm https://doi.org/10.1287/mnsc.20.5.814
import pynetgen as ng

# help(ng.netgen_generate)

ng.netgen_generate(mincost=1,    # irrelevant, needed to generate max flow problem
                   maxcost=1,    # irrelevant, needed to generate max flow problem
                   sources=1,    # single source, 0 
                   sinks=1,      # single sink, nodes-1
                   maxcap=50,    # max possible capacity on an edge
                   mincap=1,     # min possible capacity on an edge
                   supply=1,     # honestly no idea what this does, but needed to generate edges with maxcap and mincap
                   nodes=20,    # number of vertices
                   density=100, # number of edges
                   fname="/Users/noel/Desktop/git/Uni/Max flow/test.dimacs") # where save the generated graph
