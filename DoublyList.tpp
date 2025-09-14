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
    // TO DO: Implement the code for the append
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
    // TO DO: Implent code for getElement at position -Done
    if (position < 0 || position >= this->length) {
        throw string("getElement: error, position out of bounds");
    }
    
    Node* curr = nullptr;
    
    if (position <= getLength()) {
        curr = header->next;
        for (int i = 0; i < position; i++, curr = curr->next);
    }   

    return curr->value;
}

template <typename T>
int DoublyList<T>::getLength() const {
    return this->length;
}


template <typename T>
void DoublyList<T>::insert(int position, const T& elem) {
  // TO DO: Implement code to insert an element to list
        if (position < 0 || position >= this->length) {
        throw string("insert: error, position out of bounds");
    }
    
    Node* n          = new Node(elem);
    Node* curr       = nullptr;
    if (position <= getLength()) {
        curr = header->next;
        for (int i = 0; i < position; i++, curr = curr->next);
    }

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
    // TO DO: Implement code to remove element at given position
        if (position < 0 || position >= this->length) {
        throw string("remove: error, position out of bounds");
    }

    Node* curr       = nullptr;
    if (position <= getLength()) {
        curr = header->next;
        for (int i = 0; i < position; i++, curr = curr->next);
    }

    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;

    delete curr;

    this->length--;

}

template <typename T>
bool DoublyList<T>::search(const T& elem) const {
    // TO DO: Implement code to search for element - Done
    Node* curr = header->next;

    while (curr != trailer && curr->value != elem) {
        curr = curr->next;
    }

    return curr != trailer;
}

template <typename T>
void DoublyList<T>::replace(int position, const T& elem) {
    // TO DO: Add code for replace method
    if (position < 0 || position >= this->length) {
        throw string("replace: error, position out of bounds");
    }

    Node* curr       = nullptr;
    if (position <= getLength()) {
        curr = header->next;
        for (int i = 0; i < position; i++, curr = curr->next);
    }
    curr->value = elem;
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
