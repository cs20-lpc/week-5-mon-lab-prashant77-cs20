template <typename T>
DoublyList<T>::DoublyList()
: header(new Node), trailer(new Node) {
    header->next  = trailer;
    trailer->prev = header;
}

template <typename T>
DoublyList<T>::DoublyList(const DoublyList<T>& copyObj)
: header(new Node), trailer(new Node) {
    copy(copyObj);
}

template <typename T>
DoublyList<T>& DoublyList<T>::operator=(const DoublyList<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
DoublyList<T>::~DoublyList() {
    clear();
    delete header;
    delete trailer;
    header = trailer = nullptr;
}

template <typename T>
void DoublyList<T>::append(const T& elem) {
    Node* n             = new Node(elem, trailer, trailer->prev);
    trailer->prev->next = n;
    trailer->prev       = n;
    this->length++;
}

template <typename T>
void DoublyList<T>::clear() {
    for (Node* curr = nullptr; header->next != trailer; ) {
        curr = header->next->next;
        delete header->next;
        header->next = curr;
    }

    trailer->prev = header;
    this->length  = 0;
}

template <typename T>
void DoublyList<T>::copy(const DoublyList<T>& copyObj) {
    this->length   = copyObj.length;
    Node* myCurr   = header;
    Node* copyCurr = copyObj.header->next;

    while (copyCurr != copyObj.trailer) {
        Node* n      = new Node(copyCurr->value);
        myCurr->next = n;
        n->prev      = myCurr;
        myCurr       = n;
        copyCurr     = copyCurr->next;
    }

    myCurr->next  = trailer;
    trailer->prev = myCurr;
}

template <typename T>
T DoublyList<T>::getElement(int position) const {
    if (position < 0 || position >= this->length) {
        throw string("getElement: error, position out of bounds");
    }

    return getNode(position)->value;
}

template <typename T>
int DoublyList<T>::getLength() const {
    return this->length;
}

template <typename T>
typename DoublyList<T>::Node* DoublyList<T>::getNode(int position) const {
    Node* curr = nullptr;
    
    if (position <= getLength() / 2) {
        curr = header->next;
        for (int i = 0; i < position; i++, curr = curr->next);
    }
    else {
        curr = trailer->prev;
        for (int i = getLength() - 1; i > position; i--, curr = curr->prev);
    }

    return curr;
}

template <typename T>
void DoublyList<T>::insert(int position, const T& elem) {
    if (position < 0 || position >= this->length) {
        throw string("insert: error, position out of bounds");
    }
    
    Node* n          = new Node(elem);
    Node* curr       = getNode(position);
    curr->prev->next = n;
    n->prev          = curr->prev;
    n->next          = curr;
    curr->prev       = n;

    this->length++;
}

template <typename T>
bool DoublyList<T>::isEmpty() const {
    return this->length  == 0
        && header->next  == trailer
        && trailer->prev == header;
}

template <typename T>
void DoublyList<T>::remove(int position) {
    if (position < 0 || position >= this->length) {
        throw string("remove: error, position out of bounds");
    }

    Node* curr       = getNode(position);
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;

    delete curr;

    this->length--;
}

template <typename T>
void DoublyList<T>::removeValue(const T& elem) {
    Node* curr = header->next;
    while (curr != trailer && curr->value != elem) {
        curr = curr->next;
    }

    if (curr == trailer) {
        throw string("removeValue: error, unable to find the value");
    }
    else {
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        this->length--;
    }
}

template <typename T>
void DoublyList<T>::replace(int position, const T& elem) {
    if (position < 0 || position >= this->length) {
        throw string("replace: error, position out of bounds");
    }

    getNode(position)->value = elem;
}

template <typename T>
bool DoublyList<T>::search(const T& elem) const {
    Node* curr = header->next;
    
    while (curr != trailer && curr->value != elem) {
        curr = curr->next;
    }

    return curr != trailer;
}

template <typename T>
ostream& operator<<(ostream& outStream, const DoublyList<T>& myObj) {
    if (myObj.isEmpty()) {
        outStream << "List is empty, no elements to display.\n";
    }
    else {
        typename DoublyList<T>::Node* curr = myObj.header->next;
        while (curr != myObj.trailer) {
            outStream << curr->value;
            if (curr->next != myObj.trailer) {
                outStream << " <--> ";
            }
            curr = curr->next;
        }
        outStream << endl;
    }

    return outStream;
}
