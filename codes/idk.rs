fn main() {
    let mut s = String::new();
    let mut i = 0;
    while i < 10 {
        s.push_str(&i.to_string());
        i += 1;
    }
    println!("{}", s);
}