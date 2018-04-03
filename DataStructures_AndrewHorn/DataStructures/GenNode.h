#pragma once
#include <string>
#include <list>
#include <iterator>
#include "Exception.h"

using std::list;
using std::string;
using std::iterator;

class GenNode
{
private: 
	string path_;
	list <GenNode*> children_;
	GenNode * parent_;
	void copy(const GenNode &copy) noexcept;
	bool dir_;
public:
	GenNode();
	GenNode(const string path, GenNode * const parent, bool isDir);
	GenNode(const wchar_t *path, GenNode * const parent, bool isDir);
	GenNode(const GenNode &copy);
	~GenNode();

	const string GetPath() const noexcept;
	const list <GenNode*>* GetChildren() const noexcept;
	void SetPath(const string path);
	void AddChild(GenNode * const child);
	void RemoveChild(const string rem);
	void SetParent(GenNode * const parent) noexcept;
	const GenNode* GetParent() const noexcept;
	void Purge() noexcept;
	void SetDir(bool) noexcept;
	const bool IsDir() const noexcept;
	GenNode& operator=(const GenNode &rhs) noexcept;
};

void GenNode::copy(const GenNode &copy) noexcept
{
	path_ = copy.GetPath();
	children_.clear();
	children_ = *copy.GetChildren();
	dir_ = copy.IsDir();
}

GenNode::GenNode()
	: path_(""), children_(), parent_(nullptr), dir_(false) {}

GenNode::GenNode(const string path, GenNode * const parent, bool isDir)
	: path_(path), parent_(parent), dir_(isDir) {}

GenNode::GenNode(const wchar_t *path, GenNode * const parent, bool isDir)
	: parent_(parent), dir_(isDir)
{
	size_t i = 0;
	while (path[i] != L'\0')
		path_ += static_cast<char>(path[i++]);
}

GenNode::GenNode(const GenNode &copy) { this->copy(copy); }

GenNode::~GenNode() { Purge(); }

const string GenNode::GetPath() const noexcept { return path_; }

const list<GenNode*>* GenNode::GetChildren() const noexcept { return &children_; }

void GenNode::SetPath(const string path) { path_ = path; }

void GenNode::AddChild(GenNode * const child)
{
	if (IsDir())
		children_.emplace_back(child);
	else
		throw Exception("Can only add children to directories.");
}

void GenNode::RemoveChild(const string rem)
{
	bool found = false;
	GenNode* temp = nullptr;
	auto it = children_.begin();
	while (it != children_.end() && !found)
		if ((*it)->GetPath() == rem)
		{
			children_.remove(*it);
			found = true;
		}
	if (!found)
		throw Exception("Unable to remove, does not exist.");
}

void GenNode::SetParent(GenNode * const parent) noexcept { parent_ = parent; }

const GenNode* GenNode::GetParent() const noexcept { return parent_; }

void GenNode::Purge() noexcept { path_ = ""; children_.clear(); }

void GenNode::SetDir(bool dir) noexcept { dir_ = dir; }

const bool GenNode::IsDir() const noexcept { return dir_; }

GenNode& GenNode::operator=(const GenNode &rhs) noexcept { copy(rhs); return *this; }