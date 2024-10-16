/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
struct returnType {
    bool isPerfect;  // Is this subtree perfect?
    int size;        // Size of this subtree (number of nodes)
    int height;      // Height of this subtree
};

// Function to find the largest perfect subtree and collect their sizes
returnType findPerfectBinaryTree(TreeNode* root, vector<int>& perfectSubtreeSizes) {
    returnType rt;

    // If the node is NULL, it is a perfect subtree with size 0 and height 0
    if (root == NULL) {
        rt.isPerfect = true;
        rt.size = 0;
        rt.height = 0;
        return rt;
    }

    // Recursively check the left and right subtrees
    returnType lv = findPerfectBinaryTree(root->left, perfectSubtreeSizes);
    returnType rv = findPerfectBinaryTree(root->right, perfectSubtreeSizes);

    // If both left and right subtrees are perfect and have the same height
    if (lv.isPerfect && rv.isPerfect && lv.height == rv.height) {
        rt.height = lv.height + 1;
        rt.size = lv.size + rv.size + 1;  // Total size includes left + right + root

        // Store the size of the perfect subtree
        perfectSubtreeSizes.push_back(rt.size);
        rt.isPerfect = true;
    } else {
        // This subtree is not perfect
        rt.isPerfect = false;
        rt.size = max(lv.size, rv.size);
        rt.height = max(lv.height, rv.height);
    }

    return rt;
}

class Solution {
public:
    int kthLargestPerfectSubtree(TreeNode* root, int k) {
        vector<int> perfectSubtreeSizes;  // Vector to store sizes of perfect subtrees

        // Find all perfect subtrees and their sizes
        findPerfectBinaryTree(root, perfectSubtreeSizes);

        // Sort the sizes in descending order
        sort(perfectSubtreeSizes.begin(), perfectSubtreeSizes.end(), greater<int>());

        // If there are fewer than k perfect subtrees, return -1
        if (k > perfectSubtreeSizes.size()) {
            return -1;
        }

        // Return the k-th largest perfect subtree size
        return perfectSubtreeSizes[k - 1];
    }
};
