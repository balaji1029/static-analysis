// use std::{arch::x86_64::_MM_ROUND_TOWARD_ZERO, cell::RefCell, collections::{BTreeMap, BTreeSet}, fs, rc::Rc};
// use tree_sitter::{Parser, Node};
// use tree_sitter_rust;

// // fn analyze_func (node: Node, source_code: &str, level: usize) {
// //     let kind = node.kind();
// //     let start = node.start_byte();
// //     let end = node.end_byte();
// //     let _text = &source_code[start..end];
// //     for _ in 0..level {
// //         print!("\t");
// //     }
// //     println!("{}", kind);
// //     // println!("Node text: {}", text);

// //         for i in 0..node.child_count() {
// //         analyze_func(node.child(i).unwrap(), source_code, level + 1);
// //     }
// // }

// // fn num_vars (node: Node, source_code: &str, vars: &mut BTreeSet<String>) -> usize {
// //     let mut count = 0;
// //     let start = node.start_byte();
// //     let end = node.end_byte();
// //     let text = &source_code[start..end];

// //     if node.kind() == "identifier" {
// //         println!("{}", text);
// //         vars.insert(text.to_string());
// //     }

// //     for i in 0..node.child_count() {
// //         count += num_vars(node.child(i).unwrap(), source_code, vars);
// //     }
// //     count
// // }

// // fn main_1() {
// //     let file = "../codes/forloop.rs";
// //     let content = fs::read_to_string(file).expect("Something went wrong reading the file");

// //     let mut parser = Parser::new();

// //     parser.set_language(&tree_sitter_rust::LANGUAGE.into()).expect("Error loading Rust grammar");

// //     let tree = parser.parse(&content, None).expect("Failed to parse source code");
// //     let root_node = tree.root_node();

// //     let mut vars: BTreeSet<String> = BTreeSet::new();

// //     analyze_func(root_node, &content, 0);

// //     println!("{}", num_vars(root_node, &content, &mut vars));

// //     println!("Var count: {}", vars.len());
// // }

// struct Symbol {
//     name: String,
//     var_type: String,
//     // scope: String,
//     span: (usize, usize),
// }

// struct Function {
//     symbol: Symbol,
//     params: Vec<Symbol>,
//     return_type: Option<String>,
// }

// // A tree of symbol tables

// struct SymbolTable {
//     sumbols: Vec<Symbol>,
//     scope: Vec<i32>,
//     parent: Option<Rc<RefCell<SymbolTable>>>,
//     children: Vec<Rc<RefCell<SymbolTable>>>,
// }

// fn add_func (node: Node, code: &str, table: Rc<RefCell<SymbolTable>>) {
//     let kind = node.kind();
//     let start = node.start_byte();
//     let end = node.end_byte();
//     let text = &code[start..end];

//     let mut table = table.borrow_mut();

//     let mut func_name;
//     let mut func_params;
//     let mut func_return_type = None;
    
//     let mut new_scope_start = start;
//     let mut new_scope_end = end;

//     for i in 0..node.child_count() {
//         let child = node.child(i);
//         if child.is_some() {
//             if (child.unwrap().kind() == "identifier") {
//                 let start = child.unwrap().start_byte();
//                 let end = child.unwrap().end_byte();
//                 func_name = &code[start..end];
//             } 
//             else if (child.unwrap().kind() == "parameters") {
//                 // TODO: Add parameters to the function
//                 func_params = Vec::new();
//             } else if (child.unwrap().kind() == "block") {
//                 new_scope_start = child.unwrap().start_byte();
//                 new_scope_end = child.unwrap().end_byte();
//             }
//         }
//     }

//     if kind == "function_item" {
//         let symbol = Symbol {
//             name: func_name.to_string(),
//             var_type: "function".to_string(),
//             span: (start, end),
//         };
//         let function_table = Function {
//             symbol: symbol,
//             params: Vec::new(),
//             return_type: None,
//         };
//         table.sumbols.push(symbol);
//     }

//     let mut new_table = SymbolTable {
//         sumbols: Vec::new(),
//         scope: [start as i32, end as i32].to_vec(),
//         parent: Some(table.clone()),
//         children: Vec::new(),
//     };

//     for i in 0..node.child_count() {
//         let child = node.child(i);
//         if child.is_some() {
//             add_func(child.unwrap(), code, table.clone());
//         }
//     }
// }

// fn run_node (node: Node, code: &str, table: Rc<RefCell<SymbolTable>>) {
//     let kind = node.kind();
//     let start = node.start_byte();
//     let end = node.end_byte();
//     let text = &code[start..end];

//     let mut table = table.borrow_mut();

//     for i in 0..node.child_count() {
//         let child = node.child(i);
//         if child.is_some() {
//             add_func(child.unwrap(), code, table.clone());
//         }
//     }
// }

// fn build_symbol_table (source_code: &str) {
//     let mut symbols: BTreeMap<String, Symbol> = BTreeMap::new();
//     let mut parser = Parser::new();

//     parser.set_language(&tree_sitter_rust::LANGUAGE.into()).expect("Error loading Rust grammar");

//     let tree = parser.parse(&source_code, None).expect("Failed to parse source code");
    
//     let root_node = tree.root_node();
    
//     let symbol_table_head = Rc::new(RefCell::new(SymbolTable {
//         sumbols: Vec::new(),
//         scope: [root_node.start_byte() as i32, root_node.end_byte() as i32].to_vec(),
//         parent: None,
//         children: Vec::new(),
//     }));

    
// }

// fn main () {
//     let file = "../codes/forloop.rs";
//     let content = fs::read_to_string(file).expect("Something went wrong reading the file");

   

//     build_symbol_table(&content);

//     // println!("{:?}", response);
// }

use std::{fs};
use tree_sitter::{Parser, Node};
use tree_sitter_rust;

// #[derive(Debug)]
// struct Symbol {
//     name: String,
//     var_type: String,
//     span: (usize, usize),
// }

// #[derive(Debug)]
// struct SymbolTable {
//     symbols: Vec<Symbol>,
//     scope: (usize, usize),
//     parent: Option<Rc<RefCell<SymbolTable>>>,
//     children: Vec<Rc<RefCell<SymbolTable>>>,
// }

// impl SymbolTable {
//     fn new(parent: Option<Rc<RefCell<SymbolTable>>>, start: usize, end: usize) -> Rc<RefCell<Self>> {
//         Rc::new(RefCell::new(SymbolTable {
//             symbols: Vec::new(),
//             scope: (start, end),
//             parent,
//             children: Vec::new(),
//         }))
//     }

//     fn print(&self, level: usize) {
//         for _ in 0..level {
//             print!("  ");
//         }
//         println!("Scope ({}, {}):", self.scope.0, self.scope.1);
//         for symbol in &self.symbols {
//             for _ in 0..level {
//                 print!("  ");
//             }
//             println!(
//                 "  Symbol: {} (type: {}, span: ({}, {}))",
//                 symbol.name, symbol.var_type, symbol.span.0, symbol.span.1
//             );
//         }
//         for child in &self.children {
//             child.borrow().print(level + 1);
//         }
//     }
// }

// fn add_variable(node: Node, code: &str, table: Rc<RefCell<SymbolTable>>) {
//     if node.kind() != "let_declaration" {
//         return;
//     }

//     let mut var_name = String::new();
//     let mut var_type = "unknown".to_string();
//     let start = node.start_byte();
//     let end = node.end_byte();

//     // Traverse children of let_declaration to find identifier and type
//     for i in 0..node.child_count() {
//         if let Some(child) = node.child(i) {
//             match child.kind() {
//                 "identifier" => {
//                     let start = child.start_byte();
//                     let end = child.end_byte();
//                     var_name = code[start..end].to_string();
//                 }
//                 "type_identifier" => {
//                     let start = child.start_byte();
//                     let end = child.end_byte();
//                     var_type = code[start..end].to_string();
//                 }
//                 _ => {}
//             }
//         }
//     }

//     // If no identifier is found, skip (unlikely, but for safety)
//     if var_name.is_empty() {
//         return;
//     }

//     // Add variable to the symbol table
//     let symbol = Symbol {
//         name: var_name,
//         var_type,
//         span: (start, end),
//     };

//     let mut table_mut = table.borrow_mut();
//     table_mut.symbols.push(symbol);
// }

// fn add_func(node: Node, code: &str, table: Rc<RefCell<SymbolTable>>) {
//     if node.kind() == "function_item" {
//         let mut func_name = String::new();
//         let mut new_scope_start = node.start_byte();
//         let mut new_scope_end = node.end_byte();
//         let mut params = Vec::new();

//         // Traverse function children to extract name, parameters, and block
//         for i in 0..node.child_count() {
//             let child = node.child(i).unwrap();
//             match child.kind() {
//                 "identifier" => {
//                     let start = child.start_byte();
//                     let end = child.end_byte();
//                     func_name = code[start..end].to_string();
//                 }
//                 "parameters" => {
//                     // Parse parameters
//                     for j in 0..child.child_count() {
//                         if let Some(param) = child.child(j) {
//                             if param.kind() == "parameter" {
//                                 let mut param_name = String::new();
//                                 let mut param_type = "unknown".to_string();
//                                 for k in 0..param.child_count() {
//                                     if let Some(param_child) = param.child(k) {
//                                         match param_child.kind() {
//                                             "identifier" => {
//                                                 let start = param_child.start_byte();
//                                                 let end = param_child.end_byte();
//                                                 param_name = code[start..end].to_string();
//                                             }
//                                             "type_identifier" => {
//                                                 let start = param_child.start_byte();
//                                                 let end = param_child.end_byte();
//                                                 param_type = code[start..end].to_string();
//                                             }
//                                             _ => {}
//                                         }
//                                     }
//                                 }
//                                 if !param_name.is_empty() {
//                                     params.push(Symbol {
//                                         name: param_name,
//                                         var_type: param_type,
//                                         span: (param.start_byte(), param.end_byte()),
//                                     });
//                                 }
//                             }
//                         }
//                     }
//                 }
//                 "block" => {
//                     new_scope_start = child.start_byte();
//                     new_scope_end = child.end_byte();
//                 }
//                 _ => {}
//             }
//         }

//         // Create symbol for the function
//         let function_symbol = Symbol {
//             name: func_name,
//             var_type: "function".to_string(),
//             span: (node.start_byte(), node.end_byte()),
//         };

//         // Create a new scope for the function
//         let new_table = SymbolTable::new(Some(table.clone()), new_scope_start, new_scope_end);

//         // Add function and parameters to the current table
//         {
//             let mut table_mut = table.borrow_mut();
//             table_mut.symbols.push(function_symbol);
//             table_mut.symbols.extend(params);
//             table_mut.children.push(new_table.clone());
//         }

//         // Process children in the new scope
//         for i in 0..node.child_count() {
//             if let Some(child) = node.child(i) {
//                 add_func(child, code, new_table.clone());
//                 add_variable(child, code, new_table.clone());
//             }
//         }
//     } else {
//         // Process children for variables and nested functions
//         for i in 0..node.child_count() {
//             if let Some(child) = node.child(i) {
//                 add_func(child, code, table.clone());
//                 add_variable(child, code, table.clone());
//             }
//         }
//     }
// }

// fn build_symbol_table(source_code: &str) -> Rc<RefCell<SymbolTable>> {
//     let mut parser = Parser::new();
//     parser
//         .set_language(&tree_sitter_rust::LANGUAGE.into())
//         .expect("Error loading Rust grammar");

//     let tree = parser.parse(source_code, None).expect("Failed to parse source code");
//     let root_node = tree.root_node();

//     let symbol_table_head = SymbolTable::new(None, root_node.start_byte(), root_node.end_byte());
//     add_func(root_node, source_code, symbol_table_head.clone());
//     symbol_table_head
// }

fn print_ast (node: Node, source_code: &str, level: usize) {
    let kind = node.kind();
    let start = node.start_byte();
    let end = node.end_byte();
    // let text = &source_code[start..end];
    // for _ in 0..level {
    //     print!("\t");
    // }
    println!("{} {} {} {}", level, kind, start, end);

    for i in 0..node.child_count() {
        print_ast(node.child(i).unwrap(), source_code, level + 1);
    }
}

// Take command line arguments

fn get_args() -> Vec<String> {
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 2 {
        panic!("Please provide a file path as an argument.");
    }
    args
}


fn main() {

    let args = get_args();

    let file = args[1].clone();
    let content = fs::read_to_string(file).expect("Failed to read the file");

    let mut parser = Parser::new();
    parser
        .set_language(&tree_sitter_rust::LANGUAGE.into())
        .expect("Error loading Rust grammar");
    let tree = parser.parse(&content, None).expect("Failed to parse source code");
    let root_node = tree.root_node();

    let source_code = content.as_str();
    let level = 0;

    print_ast(root_node, source_code, level);
    println!("END");
}