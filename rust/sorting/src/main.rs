use std::io;
use std::io::Write;
use rand::Rng;
mod algorithms;

fn input_array() -> Vec<i32> {
    let mut input_string: String = String::new();

    // input size
    print!("Input desired array size:   ");
    io::stdout().flush().unwrap();
    io::stdin()
        .read_line(&mut input_string)
        .expect("Input error.");
    let size: usize = input_string
        .trim()
        .parse()
        .expect("Error: input is not a number.");
    input_string.clear();

    // input range_min
    print!("Input range minimum value:  ");
    io::stdout().flush().unwrap();
    io::stdin()
        .read_line(&mut input_string)
        .expect("Input error.");
    let range_min: i32 = input_string
        .trim()
        .parse()
        .expect("Error: input is not a number.");
    input_string.clear();

    // input range_max
    print!("Input range maximum value:  ");
    io::stdout().flush().unwrap();
    io::stdin()
        .read_line(&mut input_string)
        .expect("Input error.");
    let range_max: i32 = input_string
        .trim()
        .parse()
        .expect("Error: input is not a number.");
    input_string.clear();

    // generate array
    let mut array: Vec<i32> = vec![0; size];
    let mut rng = rand::rng();
    for i in 0..size {
        array[i] = rng.random_range(range_min..(range_max + 1));
    }

    array
}

fn print_array(array: &Vec<i32>) -> () {
    print!("[");
    for i in 0..(array.len() - 1) {
        print!("{}, ", array[i]);
    }
    println!("{}]", array[array.len() - 1]);
}


fn main() {
    let array: Vec<i32> = input_array();
    print!("Unsorted:        ");
    print_array(&array);

    let mut array_copy: Vec<i32> = array.clone();
    algorithms::bubble_sort(&mut array_copy);
    print!("Bubble Sort:     "); 
    print_array(&array_copy);

    array_copy = array.clone();
    algorithms::selection_sort(&mut array_copy);
    print!("Selection Sort:  ");
    print_array(&array_copy);
}

