#define max(a, b) (((a) > (b)) ? (a) : (b))

struct t_node {
  char value;
  struct t_node* left;
  struct t_node* right;
};
typedef struct t_node t_node;

t_node* insert(t_node* root_p, char value);
int search(t_node* root, char value);
t_node* make_bst(char arr[], int size);
void post_order_print(t_node* root);
void pre_order_print(t_node* root);
void in_order_print(t_node* root);
int height(t_node* root);
int count(t_node* root);
int min_value(t_node* root);
int max_value(t_node* root);
void clear(t_node* root);