use std::io;
use std::io::Write;

fn input_array() -> Vec<i32> {
    let array: Vec<i32> = Vec::new();
    let mut input_string: String = String::new();

    // input size
    print!("Input desired array size:  ");
    io::stdout().flush().unwrap();
    io::stdin()
        .read_line(&mut input_string)
        .expect("Input error.");
    let size: u8 = input_string
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
    loop {
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
        if range_max > range_min {
            break;
        } else {
            println!("Error: max range is too low");
            return array;
        }
    }
    
    // input allow_repeating

    array
}

// fn print_array(list: &mut [i32; 10]) -> () {
//     print!("[");
//     for i in 0..(list.len() - 1){
//         print!("{}, ", i);
//     }
//     println!("{}]", list[list.len() - 1]);
// }


fn main() {

    input_array();


    // let mut l: [i32; 10] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];


    // print_array(&mut l);
}

