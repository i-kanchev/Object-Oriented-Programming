#pragma once

const size_t DEFAULT_CAPACITY = 10;

template<class T>
class Vector {
	size_t size;
	size_t capacity;
	T* data;
public:
	Vector();
	Vector(const Vector<T>&);
	~Vector();

	size_t getSize() const;

	Vector<T>& operator=(const Vector<T>&);
	T& operator[](const size_t);
	const T& operator[](const size_t) const;

	void add(T&);
	void remove(const size_t);
private:
	void resize();
	void copyFrom(const Vector<T>&);
	void free();
};

template<class T>
inline Vector<T>::Vector()
{
	size = 0;
	capacity = DEFAULT_CAPACITY;
	data = new T[capacity];
}

template<class T>
inline Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
}

template<class T>
inline Vector<T>::~Vector()
{
	free();
}

template<class T>
inline size_t Vector<T>::getSize() const
{
	return size;
}

template<class T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template<class T>
inline T& Vector<T>::operator[](const size_t index)
{
	if (index < 0 || index >= size)
		throw "Invalid index";
	
	return data[index];
}

template<class T>
inline const T& Vector<T>::operator[](const size_t index) const
{
	if (index < 0 || index >= size)
		throw "Invalid index";

	return data[index];
}

template<class T>
inline void Vector<T>::add(T& element)
{
	if (size == capacity)
		resize();

	data[size++] = element;
}

template<class T>
inline void Vector<T>::remove(const size_t index)
{
	if (index < 0 || index >= size)
		throw "Invalid index";
	
	delete data[index];
	size--;
	for (size_t i = index; i < size; i++)
		data[i] = data[i + 1];
}

template<class T>
inline void Vector<T>::resize()
{
	capacity += DEFAULT_CAPACITY;

	T* temp = new T[capacity];
	for (size_t i = 0; i < size; i++)
		temp[i] = data[i];

	delete[] data;
	data = temp;
}

template<class T>
inline void Vector<T>::copyFrom(const Vector<T>& other)
{
	size = other.size;
	capacity = other.capacity;

	data = new T*[capacity];
	for (size_t i = 0; i < capacity; i++)
		data[i] = other.data[i]->clone();
}

template<class T>
inline void Vector<T>::free()
{
	for (size_t i = 0; i < size; i++)
		delete data[i];
	
	delete[] data;
}