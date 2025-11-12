
pub fn bubble_sort(array: &mut Vec<i32>) -> () {
    let mut sorted: bool = false;
    while !sorted {
        sorted = true;
        for i in 0..(array.len() - 1) {
            if array[i] > array[i + 1] {
                sorted = false;
                let temp: i32 = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }
}

pub fn selection_sort(array: &mut Vec<i32>) -> () {
    let mut lbound: usize = 0;
    while lbound < array.len() - 1 {
        for i in (lbound + 1)..array.len() {
            if array[i] < array[lbound] {
                let temp: i32 = array[lbound];
                array[lbound] = array[i];
                array[i] = temp;
            }
        }
        lbound += 1;
    }
}
