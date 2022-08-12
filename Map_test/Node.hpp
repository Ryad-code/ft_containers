#ifndef NODE_HPP
#define NODE_HPP

template <typename T>
struct  node
{
	T		value;
        struct node   *right;
        struct node   *left;
};

template <typename T>
void    place(node<T> **start, node<T> *n)
{
        node<T>    *current =  *start;
        node<T>   *prec = NULL;

        if (*start == NULL)
        {
                *start = n;
                return;
        }
        while (current)
        {
                prec = current;
                if (n->value < current->value)
                        current = current->left;
                else
                        current = current->right;
        }
        if (n->value < prec->value)
                prec->left = n;
        else
                prec->right = n;
}

template <typename  T>
void add(node<T> **start, T &value)
{
   node<T> *nouveau = new node<T>;
   nouveau->value = value;
   nouveau->right = NULL;
   nouveau->left = NULL;
   place(start, nouveau);
}

template <typename T>
void display(node<T> *start)
{
   if(start->left)
           display(start->left);
   std::cout << start->value.first << "::" << start->value.second << std::endl;
   if(start->right)
           display(start->right);
}

template <typename T>
node<T> *search(node<T> *start, T &value)
{
   node<T> *current = start;
   while(current)
   {
      if(value == current->value)
         return current;
      else if(value < current->value)
         current = current->left;
      else
         current = current->right;
   }

   return NULL;
}

template <typename T>
void n_delete(node<T> **start, node<T> *n)
{
   node<T> *right = n->right;
   node<T> *left = n->left;
   node<T> *current = *start;

   if(n == *start)
   {
      *start = right;
      if(left) 
	      place(start, left);
      delete n;
      return;
   }
   while(current)
   {
      if(current->right == n || current->left == n)
         break;

      if(n->value >= current->value)
         current = current->right;
      else
         current = current->left;
   }
   if(current->right == n)
      current->right = right;
   else
      current->left = right;
   if(left) 
	   place(start, left);
   delete n;
}

/*template <typename T>.............................MARCHE PAS
void print(node<T> *start, std::string path = "") 
{
	if (start)
	{
		print(start->left, path + "L");
		std::cout << path << ' ' << start->value.first << '_' << start->value.second;
		if (start->parent)
			std::cout << " p:" << start->parent->value.first << ' ';
		else
			std::cout << " root";
		if (start->left || start->right)
		{
			std::cout << " ";
			if (start->left)
				std::cout << "l";
			if (start->right)
				std::cout << "r";
		}
		if (start->last)
			std::cout << " last";
		std::cout << std::endl;
		print(start->right, path + "R");
	}
}*/

/*template <typename T> ............................MARCHE PAS
void clear_nodes(node<T> **start)
{
	if((*start)->left)
		clear_nodes(&(*start)->left);
	std::cout << (*start)->value.first << std::endl;
	if((*start)->right)
		clear_nodes(&(*start)->right);
}*/

#endif

