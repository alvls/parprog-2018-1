#include < vector>
#include <algorithm>
class link{
	double x;
	double z;
	link *next;
public:
	link(double _x = 100000000, double _z = 0){
		x = _x;
		z = _z;
		next = 0;
	}

	link(const link &tmp){
		x = tmp.x;
		z = tmp.z;
		next = 0;
	}

	~link(){ }

	link& operator=(link tmp){
		x = tmp.x;
		z = tmp.z;
		next = 0;
		return *this;
	}

	void SetNext(link *tmp){
		next = tmp;
	}

	link* GetNext(){
		return next;
	}

	void Setx(double tmp){
		x = tmp;
	}

	double Getx(){
		return x;
	}

	void Setz(double tmp){
		z = tmp;
	}

	double Getz() const{
		return z;
	}

	bool operator<(link const& other) { return x < other.x; }

	bool operator==(const link & obj2) const
	{
		if (x == obj2.x)
			return true;
		else
			return false;
	}
};


class cListl{
	std::vector<link> data;
public:
	cListl(){
		
	}

	cListl(cListl &tmp){
		
		data = tmp.data;
	}

	void del_cList(){
		
		data.clear();
	}

	~cListl(){
	}

	cListl &operator=(cListl& tmp){
		
		data = tmp.data;
	}

	void AddList(cListl& tmp)
	{
		for (int i = 0; i < tmp.get_count();i++)
			this->Add(tmp[i].Getx(), tmp[i].Getz());
	}

	void Add(double x, double z)
	{
		auto item = link(x, z);
		auto it = std::upper_bound(data.begin(), data.end(), item, [](link left, link right) {
			return left < right;
		});
		data.insert(it, item);

	}

	link &operator[](int j)
	{
		return data[j];
	}

	int get_count(){
		return data.size();
	}

	int get_number_on_x(double x1)
	{
		auto it = std::find(data.begin(), data.end(), link(x1, 0.0));
		if (it == data.end())
		{
			return -1; 
		}
		else
		{
			return std::distance(data.begin(), it);
		}
	}
};
