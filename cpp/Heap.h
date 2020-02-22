/*
"In pursuit of knowledge, every day something is acquired. 
In pursuit of wisdom, every day something is dropped." ~ Lao Tzu
*/
class Heap{
        public:
                Heap(int nMax){
                        t = new int[nMax+1];
                        L = 0;
                        nmax = nMax;
                }

                void insert(int x);
                int pop();
                int size();
        private:
                int *t;
                int L, nmax;
                void toTop();
                void toBottom();
};

void Heap::insert(int x){
        /* insert element x onto the heap */
        if (L > nmax)
                throw std::out_of_range("Heap is full");
        t[++L]=x;
        toTop();
}

int Heap::size(){
        /* get number of elements in the heap */
        return L;
}

void Heap::toTop(){
        int temp = t[L];
        int i = L;
        while ((i != 1) && (t[i/2]<=temp)){
                t[i] = t[i/2];
                i /= 2;
        }
        t[i] = temp;
}

int Heap::pop(){
        /* take element off the heap */
        if (L < 1)
                throw std::out_of_range("Heap is empty");
        int tmp = t[1];
        t[1] = t[L--];
        toBottom();
        return tmp;
}
void Heap::toBottom(){
        int i = 1, p;
        while ((p=2*i)<= L){
                if (p+1 <= L)
                        if (t[p] < t[p+1])
                                p++;
                if (t[i] >= t[p])
                        break;
                int temp = t[p];
                t[p] = t[i];
                t[i] = temp;
                i = p;
        }
}
