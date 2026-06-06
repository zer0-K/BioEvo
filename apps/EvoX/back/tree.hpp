#pragma once

#include <vector>
#include <string>
#include <memory>
#include <filesystem>
#include <stdexcept>
#include <functional>
#include <algorithm>

namespace fs = std::filesystem;

namespace back::tree
{

    template<typename T>
    class Tree
    {
    public:

        struct Node
        {
            ///< value of the node (typically: experiment name)
            T value;
            ///< path of the data (value is more for display)
            fs::path path;

            Node* parent = nullptr;
            std::vector<std::unique_ptr<Node>> children;

            explicit Node(T val, fs::path path_, Node* parent_ = nullptr)
                : value(std::move(val)), 
                  path(std::move(path_)),
                  parent(parent_) {}

            bool isRoot() const { return parent == nullptr; }
            bool isLeaf() const { return children.empty(); }
            size_t childCount() const { return children.size(); }
            fs::path getPath() const { return path; }
        };

        explicit Tree(T rootValue, fs::path data_path)
        {
            root_ = std::make_unique<Node>(
                std::move(rootValue),
                fs::path(data_path)
            );
        }

        Node* root() const { return root_.get(); }

        // --- Mutation ---

        Node* addChild(Node* parent, T value, std::string dir_name)
        {
            if (!parent)
                throw std::invalid_argument("Parent node is null");

            parent->children.push_back(
                std::make_unique<Node>(
                    std::move(value), 
                    parent->getPath() / dir_name,
                    parent
                )
            );

            return parent->children.back().get();
        }

        void removeChild(Node* node)
        {
            if (!node || node->isRoot())
                throw std::invalid_argument("Cannot remove null or root node");
            
            auto& siblings = node->parent->children;
            siblings.erase(
                std::remove_if(
                    siblings.begin(),
                    siblings.end(),
                    [node](const std::unique_ptr<Node>& n){ return n.get() == node; }
                ),
                siblings.end()
            );
        }

        // --- Navigation ---

        static std::vector<Node*> childrenOf(Node* node)
        {
            // Get raw pointers to a node's children (for rendering the menu)

            std::vector<Node*> result;
            result.reserve(node->children.size());
            for (auto& child : node->children)
                result.push_back(child.get());
            
            return result;
        }

        Node* findIf(std::function<bool(const T&)> pred) const
        {
            // Find the first node whose value satisfies a predicate (BFS search)
            return bfs_(root_.get(), pred);
        }

        Node* find(const T& value) const
        {
            // find by value (requires T to have operator==)
            return findIf([&](const T& v){ return v == value; });
        }

        void traverse(std::function<void(Node*)> f) const
        {
            // Call f on every node, depth-first pre-order
            dfs_(root_.get(), f);
        }

    private:
        std::unique_ptr<Node> root_;

        Node* bfs_(Node* start, std::function<bool(const T&)>& pred) const
        {
            // get the first node satisfying the given predicate

            std::vector<Node*> queue = { start };
            while (!queue.empty())
            {
                Node* cur = queue.front();
                queue.erase(queue.begin());

                if (pred(cur->value))
                    return cur;
                
                for (auto& child : cur->children)
                    queue.push_back(child.get());
            }

            return nullptr;
        }

        void dfs_(Node* node, std::function<void(Node*)>& f) const
        {
            // call f on the whole tree

            if (!node)
                return;
            
            f(node);

            for (auto& child : node->children)
                dfs_(child.get(), f);
        }
    };
} // namespace back::tree