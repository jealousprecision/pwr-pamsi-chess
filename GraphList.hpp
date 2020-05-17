#pragma once

#include <algorithm>
#include <vector>

#include <VoidType.hpp>

template<typename VertexLabel, typename EdgeLabel>
class GraphList
{
public:
    struct Vertex
    {
    public:
        Vertex(const VertexLabel data) :
            data_(data)
        {}

        friend class GraphList<VertexLabel, EdgeLabel>;

    protected:
       std::vector<unsigned> edgesOut_;
       std::vector<unsigned> edgesIn_;
        VertexLabel data_;
    };

    struct Edge
    {
    public:
        Edge(unsigned from, unsigned to, const EdgeLabel& data) :
            from_(from),
            to_(to),
            data_(data)
        {}

        friend class GraphList<VertexLabel, EdgeLabel>;

    protected:
        unsigned from_, to_;
        EdgeLabel data_;
    };

    /////////////////////////////////////////////////////////////////

    unsigned addVertex(const VertexLabel& vLabel)
    {
        vertices_.emplace_back(vLabel);
        return vertices_.size() - 1;
    }

    unsigned addEdge(unsigned from, unsigned to, const EdgeLabel& edge)
    {
        edges_.emplace_back(from, to, edge);

        auto idx = edges_.size() - 1;
        vertices_[from].edgesOut_.push_back(idx);
        vertices_[to].edgesIn_.push_back(idx);

        return idx;
    }

    /////////////////////////////////////////////////////////////////

    const VertexLabel& getVertex(unsigned vertex) const
    {
        return vertices_[vertex].data_;
    }

    const EdgeLabel& getEdge(unsigned edge) const
    {
        return edges_[edge].data_;
    }

    /////////////////////////////////////////////////////////////////

    const std::vector<unsigned>& getEdgesOut(unsigned vertex) const
    {
        return vertices_[vertex].edgesOut_;
    }

    const std::vector<unsigned>& getEdgesIn(unsigned vertex) const
    {
        return vertices_[vertex].edgesIn_;
    }

    unsigned getVertexFrom(unsigned edge) const
    {
        return edges_[edge].from_;
    }

    unsigned getVertexTo(unsigned edge) const
    {
        return edges_[edge].to_;
    }

    unsigned verticesSize() const
    {
        return vertices_.size();
    }

    unsigned edgesSize() const
    {
        return edges_.size();
    }

    void clear()
    {
        vertices_.clear();
        edges_.clear();
    }

protected:
   std::vector<Vertex> vertices_;
   std::vector<Edge> edges_;
};

template<typename EdgeLabel>
class GraphList<VoidType, EdgeLabel>
{
public:
    struct Vertex
    {
    public:
        friend class GraphList<VoidType, EdgeLabel>;

    protected:
       std::vector<unsigned> edgesOut_;
       std::vector<unsigned> edgesIn_;
    };

    struct Edge
    {
    public:
        Edge(unsigned from, unsigned to, const EdgeLabel& data) :
            from_(from),
            to_(to),
            data_(data)
        {}

        friend class GraphList<VoidType, EdgeLabel>;

    protected:
        unsigned from_, to_;
        EdgeLabel data_;
    };

    /////////////////////////////////////////////////////////////////

    GraphList() = default;
    GraphList(unsigned vertices) :
        vertices_(vertices)
    {}


    unsigned addVertex()
    {
        vertices_.emplace_back();
        return vertices_.size() - 1;
    }

    template<typename T>
    unsigned addVertex(T&&)
    {
        return addVertex();
    }

    unsigned addEdge(unsigned from, unsigned to, const EdgeLabel& edge)
    {
        edges_.emplace_back(from, to, edge);

        auto idx = edges_.size() - 1;
        vertices_[from].edgesOut_.push_back(idx);
        vertices_[to].edgesIn_.push_back(idx);

        return idx;
    }

    /////////////////////////////////////////////////////////////////

    unsigned getVertex(unsigned vertex) const
    {
        return vertex;
    }

    const EdgeLabel& getEdge(unsigned edge) const
    {
        return edges_[edge].data_;
    }

    /////////////////////////////////////////////////////////////////

    const std::vector<unsigned>& getEdgesOut(unsigned vertex) const
    {
        return vertices_[vertex].edgesOut_;
    }

    const std::vector<unsigned>& getEdgesIn(unsigned vertex) const
    {
        return vertices_[vertex].edgesIn_;
    }

    unsigned getVertexFrom(unsigned edge) const
    {
        return edges_[edge].from_;
    }

    unsigned getVertexTo(unsigned edge) const
    {
        return edges_[edge].to_;
    }

    /////////////////////////////////////////////////////////////////

    unsigned verticesSize() const
    {
        return vertices_.size();
    }

    unsigned edgesSize() const
    {
        return edges_.size();
    }

    void clear()
    {
        vertices_.clear();
        edges_.clear();
    }

protected:
   std::vector<Vertex> vertices_;
   std::vector<Edge> edges_;
};

template<typename VertexLabel>
class GraphList<VertexLabel, VoidType>
{
    struct Vertex
    {
    public:
        Vertex(const VertexLabel data) :
            data_(data)
        {}

        friend class GraphList<VertexLabel, VoidType>;

    protected:
       std::vector<unsigned> edgesOut_;
       std::vector<unsigned> edgesIn_;
        VertexLabel data_;
    };

    struct Edge
    {
    public:
        Edge(unsigned from, unsigned to) :
            from_(from),
            to_(to)
        {}

        friend class GraphList<VertexLabel, VoidType>;

    protected:
        unsigned from_, to_;
    };

    /////////////////////////////////////////////////////////////////

    unsigned addVertex(const VertexLabel& vLabel)
    {
        vertices_.push_back(vLabel);
        return vertices_.size() - 1;
    }

    unsigned addEdge(unsigned from, unsigned to)
    {
        edges_.push_back(Edge(from, to));

        auto idx = edges_.size() - 1;
        vertices_[from].edgesOut_.push_back(idx);
        vertices_[to].edgesIn_.push_back(idx);

        return idx;
    }

    const VertexLabel& getVertex(unsigned vertex) const
    {
        return vertices_[vertex].data_;
    }

    const std::vector<unsigned>& getEdgesOut(unsigned vertex) const
    {
        return vertices_[vertex].edgesOut_;
    }

    const std::vector<unsigned>& getEdgesIn(unsigned vertex) const
    {
        return vertices_[vertex].edgesIn_;
    }

    unsigned getVertexFrom(unsigned edge) const
    {
        return edges_[edge].from_;
    }

    unsigned getVertexTo(unsigned edge) const
    {
        return edges_[edge].to_;
    }

    unsigned verticesSize() const
    {
        return vertices_.size();
    }

    unsigned edgesSize() const
    {
        return edges_.size();
    }

    void clear()
    {
        vertices_.clear();
        edges_.clear();
    }

protected:
   std::vector<Vertex> vertices_;
   std::vector<Edge> edges_;
};
