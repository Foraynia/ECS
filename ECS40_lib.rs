#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn it_works() {
        let mut tree1 = Tree{root: Some(1), left: None, right: None};
        let mut tree2 = Tree{root: Some(5), left: None, right: None};
        let mut tree3 = Tree{root: Some(3), left: Some(Box::new(tree1)), right: Some(Box::new(tree2))};
        // let mut tree4 = Tree{root: Some(8), left: None, right: None};
        // let mut tree5 = Tree{root: Some(10), left: Some(Box::new(tree4)), right: None};
        // let mut tree6 = Tree{root: Some(7), left: Some(Box::new(tree3)), right: Some(Box::new(tree5))};
        assert_eq!(tree3.inorder(),vec![&1, &3, &5]);
    }
}

pub struct Tree<T> {
	root: Option<T>,
	left: Option<Box<Tree<T>>>,
	right: Option<Box<Tree<T>>>,
}

impl<T: Ord> Tree<T> {
    /// Creates an empty tree
    pub fn new() -> Self {
    	Tree{
            root: None,
            left: None,
            right: None,
        }
    }

    /// Returns `false` if `key` already exists in the tree, and `true` otherwise.
    pub fn insert(&mut self, key: T) -> bool {
    	match self.root{
    		Some(ref tree_node) => {
                if *tree_node == key{
                    return false;
                } else if key < *tree_node {
                    match self.left{
                        Some(ref mut tree) => tree.insert(key),
                        None => {
                            self.left = Some(Box::new(Tree{root: None, right: None, left: None,}));
                            match self.left{
                                Some(ref mut tree) => tree.insert(key),
                                _ => false,
                            }
                        },
                    }
                } else {
                    match self.right{
                        Some(ref mut tree) => tree.insert(key),
                        None => {
                            self.right = Some(Box::new(Tree{root: None, right: None, left: None,}));
                            match self.right{
                                Some(ref mut tree) => tree.insert(key),
                                _ => false,
                            }
                        },
                    }
                }
            },
            None => {
                self.root = Some(key);
                return true;
            },
    	}
    }

    /// Returns `true` if `key` exists in the tree, and `false` otherwise.
    pub fn find(&self, key: &T) -> bool {
        match self.root{
            Some(ref tree_node) => {
                if tree_node == key{
                    return true;
                } else if key < tree_node{
                    match self.left{
                        Some(ref tree) => tree.find(key),
                        None => false,
                    }
                } else{
                    match self.right{
                        Some(ref tree) => tree.find(key),
                        None => false,
                    }
                }
            },
            None => false,
        }
    }


    /// Returns the preorder traversal of the tree.
    pub fn preorder(&self) -> Vec<&T> {
    	let mut result: Vec<&T> = Vec::new();
        match self.root{
            Some(ref value) => {
                result.push(&value);
                if let Some(ref tree) = self.left {
                    for i in tree.preorder() {
                        result.push(i);
                    }
                } 
                if let Some(ref tree) = self.right {
                    for i in tree.preorder() {
                        result.push(i);
                    }
                }
                result
                // match self.left{
                //     Some(ref tree) => tree.preorder(),
                //     _ => match self.right{
                //         Some(ref tree) => tree.preorder(),
                //         _ => result,
                //     },
                // }
            },
            _ => result,
        }
    }

    /// Returns the inorder traversal of the tree.
    pub fn inorder(&self) -> Vec<&T> {
    	let mut result: Vec<&T> = Vec::new();
    	match self.root{
            Some(ref value) => {
                if let Some(ref tree) = self.left {
                    for i in tree.inorder() {
                        result.push(i);
                    }
                } 
                result.push(&value);
                if let Some(ref tree) = self.right {
                    for i in tree.inorder() {
                        result.push(i);
                    }
                }
                result
                // match self.left{
                //     Some(ref tree) => tree.inorder(),
                //     None => {return result;},
                // };
                // result.push(&value);
                // match self.right{
                //     Some(ref tree) => tree.inorder(),
                //     None => {return result;},
                // };
            }, 
            None => result,
        }
    }

    /// Returns the postorder traversal of the tree.
    pub fn postorder(&self) -> Vec<&T> {
    	let mut result: Vec<&T> = Vec::new();
    	match self.root{
            Some(ref value) => {
                if let Some(ref tree) = self.left {
                    for i in tree.postorder() {
                        result.push(i);
                    }
                } 
                
                if let Some(ref tree) = self.right {
                    for i in tree.postorder() {
                        result.push(i);
                    }
                }
                result.push(&value);
                result
                // match self.left{
                //     Some(ref tree) => tree.inorder(),
                //     None => {return result;},
                // };
                // match self.right{
                //     Some(ref tree) => tree.inorder(),
                //     None => {return result;},
                // };
                // result.push(&value);
            }, 
            None => result,
        }
    }
}
