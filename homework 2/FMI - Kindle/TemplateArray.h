#pragma once

template<class T>
class Array
{
	size_t capacity;
	T* data;
public:
	Array();
	Array(size_t);
	Array(const Array<T>&);
	~Array();

	T& operator[](const size_t);
	Array<T>& operator=(const Array<T>&);

	size_t size() const;

	T get(size_t) const;

	void add(T);
private:
	void copyFrom(const Array<T>&);
	void free();
};

template<class T>
inline Array<T>::Array()
{
	capacity = 0;
	data = nullptr;
}

template<class T>
inline Array<T>::Array(size_t size)
{
	capacity = size;
	data = new T[capacity];
	for (size_t i = 0; i < capacity; i++)
		data[i] = T();
}

template<class T>
inline Array<T>::Array(const Array<T>& other)
{
	copyFrom(other);
}

template<class T>
inline Array<T>::~Array()
{
	free();
}

template<class T>
inline T& Array<T>::operator[](const size_t index)
{
	if (index >= capacity)
		throw "Out of Array";
	return data[index];
}

template<class T>
inline Array<T>& Array<T>::operator=(const Array<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<class T>
inline size_t Array<T>::size() const
{
	return capacity;
}

template<class T>
inline T Array<T>::get(size_t index) const
{
	return data[index];
}

template<class T>
inline void Array<T>::add(T element)
{
	capacity++;
	T* newData = new T[capacity];
	for (size_t i = 0; i < capacity - 1; i++)
		newData[i] = data[i];
	newData[capacity - 1] = element;

	delete[] data;
	data = newData;
}

template<class T>
inline void Array<T>::copyFrom(const Array<T>& other)
{
	capacity = other.capacity;
	data = new T[capacity];
	for (size_t i = 0; i < capacity; i++)
		data[i] = other.data[i];
}

template<class T>
inline void Array<T>::free()
{
	delete[] data;
}