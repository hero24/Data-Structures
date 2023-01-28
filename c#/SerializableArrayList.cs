using System;
namespace DataStructures
{
    // Life is what happens when youre busy making other plans. -John Lennon
    [Serializable()]
    public class SerializableArrayList<T>
    {
        private static int INITIAL = 100;
        private static int RESIZE = 10;
        private T[] storage;
        private int i;
        public int Length
        {
            get
            {
                return i;
            }
        }
        public SerializableArrayList()
        {
            storage = new T[SerializableArrayList<T>.INITIAL];
        }
        public SerializableArrayList(int initial)
        {
            storage = new T[initial];
        }
        public void Add(SerializableArrayList<T> items)
        {
            for(int j = 0;j < items.Length;j++)
            {
                Add(items.Get(j));
            }
        }
        public void Add(T item)
        {
            if(i > storage.Length)
            {
                T[] tempStorage = new T[storage.Length + SerializableArrayListe<T>.RESIZE];
                for(int j=0; j < storage.Length;j++)
                {
                    tempStorage[j] = storage[j];
                }
                storage = tempStorage;
                
            }
            storage[i++] = item;
        }
        public T Get(int index)
        {
            if(index < i)
            {
                return storage[index];
            }
            throw new IndexOutOfRangeException();
        }
        public void RemoveAt(int index)
        {
            for(int j = index + 1,k=index;j < i; j++,k++)
            {
                storage[k] = storage[j];
            }
            i--;
        }
        public void Remove(T data)
        {
            for(int j = 0; j < i;j++)
            {
                if(storage[j].Equals(data))
                {
                    RemoveAt(j);
                    break;
                }
            }
        }
        public bool Contains(T data)
        {
            string dataToString = data.ToString();
            foreach(T cell in storage)
            {
                if(cell == null) break;
                string cellToString = cell.ToString();
                if(dataToString == cellToString) return true;
            }
            return false;
        }
    }
}
