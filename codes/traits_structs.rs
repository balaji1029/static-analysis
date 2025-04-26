trait Speak {
    fn speak(&self);
}

trait Move {
    fn r#move(&self);
}

trait Hunt {
    fn hunt(&self);
}

// // Composite trait
// trait Animal: Speak + Move {
//     fn describe(&self) {
//         println!("I am an animal.");
//     }
// }

// Dog struct
struct Dog {
    name: String,
}

impl Speak for Dog {
    fn speak(&self) {
        println!("{} says: Woof!", self.name);
    }
}

impl Move for Dog {
    fn r#move(&self) {
        println!("{} runs on land.", self.name);
    }
}

impl Animal for Dog {}

// Fish struct
struct Fish {
    species: String,
}

impl Speak for Fish {
    fn speak(&self) {
        println!("{} makes bubbles.", self.species);
    }
}

impl Move for Fish {
    fn r#move(&self) {
        println!("{} swims in water.", self.species);
    }
}

impl Animal for Fish {}

// Shark struct that can also hunt
struct Shark {
    name: String,
}

impl Speak for Shark {
    fn speak(&self) {
        println!("{} growls underwater.", self.name);
    }
}

impl Move for Shark {
    fn r#move(&self) {
        println!("{} glides silently.", self.name);
    }
}

impl Hunt for Shark {
    fn hunt(&self) {
        println!("{} is hunting smaller fish!", self.name);
    }
}

impl Animal for Shark {}

fn print_animal_info<T: Animal>(animal: &T) {
    animal.describe();
    animal.speak();
    animal.r#move();
}

fn main() {
    let d = Dog { name: "Rex".to_string() };
    let f = Fish { species: "Goldfish".to_string() };
    let s = Shark { name: "Bruce".to_string() };

    print_animal_info(&d);
    print_animal_info(&f);
    print_animal_info(&s);

    s.hunt();
}
