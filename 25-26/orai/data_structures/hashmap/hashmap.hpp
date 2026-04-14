#pragma once

using size_t = decltype(sizeof 0);

template <typename T>
struct hash;

template <>
struct hash<int> {
    size_t operator()(int value) const noexcept {
        value = ((value >> 16) ^ value) * 0x45d9f3b;
        value = ((value >> 16) ^ value) * 0x45d9f3b;
        value = (value >> 16) ^ value;
        return value;
    }
};

template <typename T>
struct equal_to {
    constexpr bool operator()(const T& lhs, const T& rhs) {
        return lhs == rhs;
    }
};

template <typename Key, typename T, class Hash = hash<Key>, class KeyEqual = equal_to<Key>>
class hashmap {
  private:
    struct node {
        Key key;
        T value;
        node* next;
    };

    node** buckets_;
    Hash hasher_;
    KeyEqual key_equal_;

    size_t bucket_count_;
    size_t size_;

  public:
    typedef Key key_type;
    typedef T mapped_type;

    explicit hashmap(size_t bucket_count = 32)
        : hasher_(Hash{}), key_equal_(KeyEqual{}), bucket_count_(bucket_count), size_(0) {
        buckets_ = new node*[bucket_count_]();
    }

    ~hashmap() {
        for(size_t i = 0; i < bucket_count_; ++i) {
            node* current = buckets_[i];
            while(current) {
                node* _ = current;
                current = current->next;
                delete _;
            }
        }
        delete[] buckets_;
    }

    mapped_type* find(const key_type& key) {
        size_t index = hasher_(key) % bucket_count_;
        node* current = buckets_[index];

        while(current) {
            if(key_equal_(current->key, key)) {
                return &current->value;
            }
            current = current->next;
        }
        return nullptr;
    }

    const mapped_type* find(const key_type& key) const {
        size_t index = hasher_(key) % bucket_count_;
        node* current = buckets_[index];

        while(current) {
            if(key_equal_(current->key, key)) {
                return &current->value;
            }
            current = current->next;
        }
        return nullptr;
    }

    bool contains(const key_type& key) {
        return find(key) != nullptr;
    }

    bool insert(const key_type& key, const mapped_type& value) {
        if(find(key)) {
            return false;
        }

        size_t index = hasher_(key) % bucket_count_;
        node* new_node = new node{key, value, buckets_[index]};
        buckets_[index] = new_node;
        ++size_;
        return true;
    }

    bool erase(const key_type& key) {
        size_t index = hasher_(key) % bucket_count_;
        node* current = buckets_[index];
        node* prev = nullptr;

        while(current) {
            if(key_equal_(current->key, key)) {
                if(prev) {
                    prev->next = current->next;
                }
                else {
                    buckets_[index] = current->next;
                }
                delete current;
                --size_;
                return true;
            }
        }
        return false;
    }

    mapped_type& operator[](const key_type& key) {
        size_t index = hasher_(key) % bucket_count_;
        node* current = buckets_[index];

        while(current) {
            if(key_equal_(current->key, key)) {
                return current->value;
            }
            current = current->next;
        }

        node* new_node = new node{key, mapped_type{}, buckets_[index]};
        buckets_[index] = new_node;
        ++size_;
        return new_node->value;
    }

    mapped_type& at(const key_type& key) {
        mapped_type* result = find(key);
        if(!result) {
            throw;
        }
        return *result;
    }

    const mapped_type& at(const key_type& key) const {
        const mapped_type* result = find(key);
        if(!result) {
            throw;
        }
        return *result;
    }

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    size_t max_bucket_count() const {
        return bucket_count_;
    }

    float load_factor() const {
        if(bucket_count_ == 0) {
            return 0.0f;
        }

        return static_cast<float>(size_) / static_cast<float>(bucket_count_);
    }

    constexpr size_t sizeof_node() const {
        return sizeof(node);
    }
};
