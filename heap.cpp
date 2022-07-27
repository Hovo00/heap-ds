#include <iostream>
#include <vector>
#include <initializer_list>

class heap {
public:
	heap();
	heap(std::initializer_list<int>);
	heap(const heap&);
	heap(heap&&) noexcept;
public:
	heap& operator = (const heap&);
	heap& operator = (heap&&) noexcept;
	friend std::ostream& operator << (std::ostream&, const heap&);
    bool operator == (const heap&);
	bool operator != (const heap&);
public:
	void insert(int);
	int height();
	bool delete_element(int);
	int extract_max_element();
	int linear_search(int);
private:
	void build_heap();
	int parent(int);
	void max_heapify(int);
	int left(int);
	int right(int);
private:
	std::vector<int> m_arr;
	int m_size;
};


int main() {
	heap myheap({ 1, 4, 5, -5, 0, 8, 12, 144, -35 });
	heap other(myheap);
	std::cout << other;
	std::cout << myheap;
	myheap.insert(19);
	myheap.insert(-7);
	myheap.extract_max_element();
	std::cout << myheap;
	myheap.delete_element(12);
	myheap.delete_element(-35);
	std::cout << myheap;
	
}

void heap::build_heap() {
	for (int i = (m_size >> 1); i >= 0; --i) {
		max_heapify(i);
	}
}

int heap::parent(int pos) {
	return (pos - 1) >> 1;
}

void heap::max_heapify(int pos) {
	int left_ = left(pos);
	int right_ = right(pos);
	int max_pos = pos;
	if (left_ < m_size && m_arr[left_] > m_arr[pos]) {
		max_pos = left_;
	}
	if (right_ < m_size && m_arr[right_] > m_arr[max_pos]) {
		max_pos = right_;
	}
	if (pos != max_pos) {
		std::swap(m_arr[pos], m_arr[max_pos]);
		max_heapify(max_pos);
	}
}

int heap::left(int pos) {
	return (pos << 1) + 1;
}

int heap::right(int pos) {
	return (pos << 1) + 2;
}
heap::heap() : m_size(0) {}

heap::heap(std::initializer_list<int> list) {
	for (auto &i : list) {
		m_arr.push_back(i);
	}
	m_size = list.size();
	build_heap();
}

heap::heap(const heap& oth) {
	operator=(oth);
}

heap::heap(heap&& oth) noexcept : m_size(std::move(oth.m_size)) , m_arr(std::move(oth.m_arr)) {}

heap& heap::operator=(const heap& oth)
{
	if (&oth != this) {
		m_size = oth.m_size;
		m_arr = oth.m_arr;
	}
	return *this;
}

heap& heap::operator=(heap&& other) noexcept
{
	m_size = std::move(other.m_size);
	m_arr = std::move(other.m_arr);
	return *this;
}

bool heap::operator==(const heap& oth)
{
	if (oth.m_size != m_size) { return false;}
	for (int i = 0; i < m_size; ++i){
		if (m_arr[i] != oth.m_arr[i]) { return false; }
	}
	return true;
}

bool heap::operator!=(const heap& oth)
{
	return !operator==(oth);
}

void heap::insert(int num)
{
	m_arr.push_back(num);
	++m_size;
	int pos = m_size - 1;
	int par = parent(pos);
	while (m_arr[pos] > m_arr[par] && par >= 0) {
		std::swap(m_arr[pos], m_arr[par]);
		pos = par;
		par = parent(pos);
	}

}

int heap::height()
{
	int temp = m_size;
	int height = -1;
	while (temp) {
		temp >>= 1;
		++height;
	}
	return height;
}

bool heap::delete_element(int num)
{
	int pos = linear_search(num);
	if (!pos) { return false; }
	if (pos > m_size >> 1) {
		std::swap(m_arr[pos], m_arr[m_size - 1]);
		m_arr.pop_back();
		--m_size;
	}
	else {
		std::swap(m_arr[pos], m_arr[m_size - 1]);
		m_arr.pop_back();
		--m_size;
		max_heapify(pos);
	}
	return true;
}

int heap::extract_max_element()
{
	std::swap(m_arr[0], m_arr[m_size - 1]);
	int retur = m_arr[m_size - 1];
	m_arr.pop_back();
	--m_size;
	max_heapify(0);
	return retur;
}

int heap::linear_search(int elem)
{
	for (int i = 0; i < m_size; ++i) {
		if (m_arr[i] == elem) {
			return i;
		}
	}
	return -1;
}

std::ostream& operator<<(std::ostream& out, const heap& myheap) {
	out << std::endl;
	for (auto i : myheap.m_arr) {
		out << i << " ";
	}
	return out;
}
