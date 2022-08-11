

typedef struct  s_node
{
        int             value;
        struct s_node   *right;
        struct s_node   *left;
}                       node;


void    place(node **start, node *n)
{
        node    *current =  *start;
        node    *prec = NULL;

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

void add(node **start, int value)
{
   node* nouveau = new node;
   nouveau->value = value;
   nouveau->right = NULL;
   nouveau->left = NULL;
   place(start, nouveau);
}

void display(node* start)
{
   if(start->left)
           display(start->left);
   std::cout << start->value << std::endl;
   if(start->right)
           display(start->right);
}

node* search(node *start, int value)
{
   node* current = start;
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

void n_delete(node **start, node *n)
{
   node* right = n->right;
   node* left = n->left;
   node* current = *start;

   // Cas délicat : si on supprime la racine?
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
   // Courant pointe maintenant vers le noeud précédent le
   // noeud à supprimer.
   if(current->right == n)
      current->right = right;
   else
      current->left = right;
   // Et puis on replace l'autre fils du noeud disparu
   if(left) 
	   place(start, left);
   // Enfin, on libère l'objet noeud de ses obligations
   delete n;
}

