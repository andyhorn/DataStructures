#pragma once
#include "GenNode.h"

class GenTree
{
private:
	GenNode * root_;
	GenNode * workingDir_;
	size_t count_;
	void copy(GenNode *dir) noexcept;
	void depthFirst(void(visit(GenNode *)), GenNode * const dir) const noexcept;
	void purge(GenNode *) noexcept;
	void copyNode(GenNode *node) noexcept;
protected:
	GenNode * getRoot() const noexcept;
public:
	GenTree();
	GenTree(const GenTree &copy);
	~GenTree();

	GenNode * const GetRoot() const noexcept;
	GenNode * const GetWorkingDir() const noexcept;
	void SetRoot(GenNode * const root) noexcept;
	void SetWorkingDir(GenNode * const dir) noexcept;
	void PurgeTree() noexcept;
	int GetCount() const noexcept;
	void AddNode(GenNode * const node);
	void DepthFirst(void(visit(GenNode*)));
};

GenTree::GenTree()
	: root_(nullptr), workingDir_(nullptr), count_(0) {}

GenTree::GenTree(const GenTree &copyThis)
	: root_(nullptr), workingDir_(nullptr), count_(0)
{ 
	copy(copyThis.getRoot()); 
}

GenTree::~GenTree()
{
	if (root_ != nullptr)
		purge(root_);
}

inline GenNode * const GenTree::GetRoot() const noexcept { return root_; }

inline GenNode * const GenTree::GetWorkingDir() const noexcept { return workingDir_; }

inline void GenTree::SetRoot(GenNode * const root) noexcept { root_ = root; }

inline void GenTree::SetWorkingDir(GenNode * const dir) noexcept { workingDir_ = dir; }

inline void GenTree::PurgeTree() noexcept
{
	if (root_ != nullptr)
		purge(root_);
}

inline int GenTree::GetCount() const noexcept { return static_cast<int>(count_); }

void GenTree::copy(GenNode *dir) noexcept
{
	if (dir != nullptr)
	{
		copyNode(dir);
		auto node = dir->GetChildren()->begin();
		while (node != dir->GetChildren()->end())
		{
			if ((*node)->IsDir())
			{
				copy(*node);
				SetWorkingDir(dir);
			}
			else
				copyNode(*node);
			node++;
		}
	}
}

void GenTree::copyNode(GenNode *node) noexcept
{
	// AddNode will change 'parent' pointer to current working directory anyway.
	AddNode(new GenNode(node->GetPath(), nullptr, node->IsDir()));
}

inline void GenTree::depthFirst(void(visit(GenNode *)), GenNode * const dir) const noexcept
{
	if (dir->GetChildren()->size() > 0)
	{
		auto cur = dir->GetChildren()->begin();
		size_t size = dir->GetChildren()->size();
		for (size_t i = 0; i < size; i++, cur++)
		{
			if ((*cur)->IsDir())
				depthFirst(visit, *cur);
			else
				visit(*cur);
		}
	}
}

void GenTree::AddNode(GenNode * const node)
{
	if (root_ == nullptr)
	{
		if (node->IsDir())
		{
			root_ = node;
			workingDir_ = node;
			count_++;
		}
		else
			throw Exception("Root must be a directory.");
	}
	else
	{
		workingDir_->AddChild(node);
		node->SetParent(workingDir_);
		count_++;
		if (node->IsDir())
			workingDir_ = node;
	}
}

inline void GenTree::DepthFirst(void(visit(GenNode *)))
{
	if (root_ == nullptr)
		throw Exception("Can't traverse an empty tree.");
	else
		depthFirst(visit, root_);
}

inline void GenTree::purge(GenNode *dir) noexcept
{
	if (dir != nullptr)
	{
		auto del = dir->GetChildren()->cbegin();
		while (del != dir->GetChildren()->end())
		{
			if (!(*del)->IsDir())
				delete *del;
			else
				purge(*del);
			del++;
		}
		delete dir;
	}
}

inline GenNode * GenTree::getRoot() const noexcept { return root_; }