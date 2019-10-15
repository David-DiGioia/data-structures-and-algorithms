#pragma once
#include <unordered_map>
#include <string>
#include <memory>

template <typename T>
class BasicTrie
{
	struct Node
	{
		std::unordered_map<T, std::unique_ptr<Node>> m;
		bool end;
		Node(bool end_) : end{ end_ }
		{}
	};

	void insertRec(std::unique_ptr<Node>& head, const std::basic_string<T>& str, int i)
	{
		if (i == str.size())
			return;

		// if we don't have this child, add it
		if (head->m.find(str[i]) == head->m.end())
			head->m[str[i]] = std::make_unique<Node>(i == (int)str.size() - 1);

		insertRec(head->m[str[i]], str, i + 1);
	}

	bool contains(const std::basic_string<T>& str, bool prefix)
	{
		if (!prefix && str.empty())
			return false;

		Node* cur{ m_head.get() };

		for (int i{ 0 }; i < (int)str.size(); cur = cur->m[str[i++]].get())
			if (cur->m.find(str[i]) == cur->m.end())
				return false;
		return prefix || cur->end;
	}

public:
	BasicTrie() : m_head{ std::make_unique<Node>(false) }
	{}

	void insert(const std::basic_string<T>& str)
	{
		insertRec(m_head, str, 0);
	}

	bool containsPrefix(const std::basic_string<T>& str)
	{
		return contains(str, true);
	}

	bool contains(const std::basic_string<T>& str)
	{
		return contains(str, false);
	}


private:
	std::unique_ptr<Node> m_head;
};

typedef BasicTrie<char> Trie;