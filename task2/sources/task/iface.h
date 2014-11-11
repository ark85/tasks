/**
 * @file: task/iface.h 
 * Interface of a programming task 2
 */
#include "../Utils/utils_iface.h"
#include <unordered_set>
#include <list>

/* namespaces import */
using namespace Utils;

//Debug assert with diagnostic info
#if !defined(GRAPH_ASSERTXD)
#    define GRAPH_ASSERTXD(cond, what) ASSERT_XD(cond, "Graph", what)
#endif

// Simple debug assert
#if !defined(GRAPH_ASSERTD)
#    define GRAPH_ASSERTD(cond) ASSERT_XD(cond, "Graph", "")
#endif

/**
 * Namespace for the programming task
 */
namespace Task
{
    //
    // Graph representation template
    // @param NodeT class representing nodes of graph, should be inherited from Graph::Node
    // @param EdgeT class representing edges of graph, should be inherited from Graph::Edge
    //
    template < class NodeT, class EdgeT> class Graph
    {
    public:
        typedef UInt32 UId; //< Unique id type for node and edge
        static const UId INVALID_UID = (UId) (-1);

        class Error: public std::exception
        {
        };


        //
        // Graph node representation
        //
        class Node
        {
        public:
            //---- Iterator types ----
            class pred_iterator // iterator for node's predecessor edges
			{
				public:
					pred_iterator(const pred_iterator &edge_Iterator)
					{
						new_iterator = edge_Iterator;
					}
					bool operator!=(const pred_iterator &Right_Hand_Edge_Iterator)
					{
						return new_iterator != Right_Hand_Edge_Iterator.new_iterator;
					}
					pred_iterator &operator++()
					{
						new_iterator++;
						return *this;
					}
					bool operator==(const pred_iterator &Right_Hand_Edge_Iterator)
					{
						return new_iterator == Right_Hand_Edge_Iterator.new_iterator;
					}

					EdgeT operator*()
					{
						return *new_iterator;
					}
			private:
				typename std::list<EdgeT>::iterator new_iterator;
			};
            class succ_iterator  // iterator for node's successor edges
			{
			    public:
					succ_iterator(const succ_iterator &edge_Iterator)
					{
						new_iterator = edge_Iterator;
					}
					bool operator==(const succ_iterator &Right_Hand_Edge_Iterator)
					{
						return new_iterator == Right_Hand_Edge_Iterator.new_iterator;
					}
					succ_iterator &operator++()
					{
						new_iterator++;
						return *this;
					}
					bool operator!=(const succ_iterator &Right_Hand_Edge_Iterator)
					{
						return new_iterator != Right_Hand_Edge_Iterator.new_iterator;
					}
					
					EdgeT operator*()
					{
						return *new_iterator;
					}
			private:
				typename std::list<EdgeT>::iterator new_iterator;
			};

            pred_iterator preds_begin() // Get iterator to the first predecessor edge
			{
				pred_iterator a(pred_edge.begin());
				return a;
			}
            pred_iterator preds_end()   // Get end iterator for the predecessors
			{
				pred_iterator a(pred_edge.end());
				return a;
			}

            succ_iterator succs_begin() // Get iterator to the first successor edge
			{
				succ_iterator a(succ_edge.begin());
				return a;
			}
            succ_iterator succs_end()   // Get end iterator for the successors
			{
				succ_iterator a(succ_edge.end());
				return a;
			}

            Graph& graph()  // Get the graph reference
			{
				return node_graph;
			}
            UId uid() const // Get the node's unique id 
			{
				return node_id;
			}

            EdgeT& first_pred() // Convinience routine returns first predecessor edge or throws an exception
			{
				if (pred_edge.size())
				{
					return pred_edge.front();
				}
				else return NULL;
			}
			EdgeT& first_succ() // Convinience routine returns first successor edge or throws an exception
			{
				if (succ_edge.size())
				{
					return succ_edge.front();
				}
				else return NULL;
				
			}
            
            UInt32 num_preds() const // Get the number of predecessors
			{
				return pred_edge.size;
			}
            UInt32 num_succs() const // Get the number of successors
			{
				return succ_edge.size;
			}

        protected:
            Node( Graph& g) // Constructor of the node
			{
				count_id = count_id + 1;
				node_id = count_id;
				node_graph = &g;
			}
            virtual ~Node()
			{
				free(pred_edge);
				free(succ_edge);
			}
        private:
            // ---- Default  and copy constructors turned off ---
            Node()
			{
				count_id = count_id + 1;
				node_id = count_id;
			}
            Node(const Node &n);
			list<EdgeT> pred_edge;
			list<EdgeT> succ_edge;
            UId node_id;
			static int count_id;
			Graph* node_graph;
            // ---- The internal implementation routines ----

            // ---- The data involved in the implementation ----
        };

        // 
        // Graph edge representation
        //
        class Edge
        {
        public:
            NodeT &pred() // Get edge predecessor
			{
				return pred_node;
			}
            NodeT &succ() // Get edge successor
			{
				return succ_node;
			}

            Graph& graph() // Get the graph
			{
				return edge_graph;
			}
            UId uid() const // Get the edge's unique id
			{
				return edge_id;
			}
        protected:
            Edge( NodeT& p, NodeT& s) // Construct an edge between given nodes
			{
				count_id++;
				edge_id = count_id;
				pred_node = &p;
				succ_node = &s;
				edge_graph = &p.graph();
			}
            virtual ~Edge();
        private:
        // ---- Default  and copy constructors turned off ---
            Edge();
            Edge( const Edge &e);
			UId edge_id;
			Graph* edge_graph;
			static int coun_id;
			NodeT* pred_node;
			NodeT* succ_node;
			
			
        // ---- The internal implementation routines ----

        // ---- The data involved in the implementation ----
    };

    public:
    // ---- Graph interface ----
        class node_iterator // Iterator for the graph's nodes
		{
			public:
				node_iterator(const node_iterator& graph_iterator)
				{
					 new_iterator = graph_iterator;
				}
				node_iterator &operator++()
				{
					new_iterator++;
					return *this;
				}
				bool operator!=(const node_iterator& Right_Hand_Graph_Iterator)
				{
					return new_iterator != Right_Hand_Graph_Iterator.new_iterator;
				}
				bool operator==(const node_iterator& Right_Hand_Graph_Iterator)
				{
					return new_iterator == Right_Hand_Graph_Iterator.new_iterator;
				}
				NodeT operator*()
				{
					return *new_Iterator;
				}
		private:
			typename std::list<NodeT>::iterator new_iterator;
		};
        class edge_iterator // Iterator for the graph's edges
		{
			public:
				edge_iterator(const edge_iterator& graph_iterator)
				{
					 new_iterator = graph_iterator;
				}
				edge_iterator &operator++()
				{
					new_iterator++;
					return *this;
				}
				EdgeT operator*()
				{
					return *new_iterator;
				}
				bool operator!=(const edge_iterator& Right_Hand_Graph_Iterator)
				{
					return new_iterator != Right_Hand_Graph_Iterator.new_iterator;
				}
				bool operator==(const edge_iterator& Right_Hand_Graph_Iterator)
				{
					return new_iterator == Right_Hand_Graph_Iterator.new_iterator;
				}
		private:
			typename std::list<EdgeT>::iterator new_iterator;
		};
               
        node_iterator nodes_begin() // Get the iterator to the first node
		{
			node_iterator a(node_list.begin());
			return a;
		}
        node_iterator nodes_end()   // Get the end iterator for the nodes
		{
			node_iterator a(node_list.end());
			return a;
		}

        edge_iterator edges_begin() // Get the iterator to the first edge
		{
			edge_iterator a(edge_list.begin());
			return a;
		}
        edge_iterator edges_end()   // Get the end iterator for the edges
		{
			edge_iterator a(edge_list.end());
			return a;
		}

        UInt32 num_nodes() const // Get the number of nodes
		{
			return node_list.size;
		}
        UInt32 num_edges() const // Get the number of edges
		{
			return edge_list.size;
		}

        NodeT &create_node()                   // Create a new node and return reference to it
		{
			NodeT new_node = new NodeT(*this);
			node_list.insert(new_node);
			return new_node;
		}
        EdgeT &create_edge( NodeT& pred, NodeT& succ) // Create a new edge between given nodes
		{
			EdgeT new_edge = new EdgeT(pred, succ);
			edge_list.insert(new_edge);
			return new_edge;
		}
    
        void remove( NodeT& node) // Remove and delete node
		{
			for (succ_iterator iterator = node.succs_begin(); iterator != node.succs_end(); iterator++)
			{
				delete(*iterator);
			}
			for (pred_iterator iterator = node.pred_begin(); iterator != node.pred_end(); iterator++)
			{
				delete(*iterator);
			}
		}
        void remove( EdgeT& edge) // Remove and delete edge
		{
			for (succ_iterator iterator = edge.succs_begin(); iterator != edge.succs_end(); iterator++)
			{
				delete(*iterator);
			}
			for (pred_iterator iterator = edge.pred_begin(); iterator != edge.pred_end(); iterator++)
			{
				delete(*iterator);
			}
		}

        virtual ~Graph(); // Destructor, deletes all nodes and edges
    private:
        // ---- The internal implementation routines ----
		list<EdgeT> edge_list;
		list<NodeT> node_list;
        // ---- The data involved in the implementation ----
    };

    bool uTest( UnitTest *utest_p);
};

#include "graph_impl.h"
