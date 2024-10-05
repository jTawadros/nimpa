#include <vector>


class LineTracker {
    public:
        LineTracker();

        void addNewLine(int position);
        void removeNewLine(int position);

        // Given a cursor pos from the gap buffer,
        // we retrieve the appropriate line number.
        int getLineFromBuffer(int position) const;
        int getLineStart(int lineNumber) const;
        int getLineEnd(int lineNumber) const;

    private:

        struct Node {
            int lineStart;
            Node* left;
            Node* right;
            int height;

            Node(int position) : lineStart(position), left(nullptr), right(nullptr), height(1) {}

        };

        Node* root;
        Node* insert(Node* node, int position);
        Node* remove(Node* node, int position);
        Node* balance(Node* node);

        int height(Node* node);
        int getBalanceFactor(Node* node);

        Node* rotateLeft(Node* node);
        Node* rotateRight(Node* node);

};
