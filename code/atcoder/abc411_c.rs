use std::io::{self, Read};
use std::str;

pub struct FastReader {
    buf: Vec<u8>,
    pos: usize,
}

impl FastReader {
    /// Create a new FastReader by reading all stdin into an internal buffer
    pub fn new() -> Self {
        let mut buf = Vec::new();
        io::stdin()
            .read_to_end(&mut buf)
            .expect("Failed to read stdin");
        FastReader { buf, pos: 0 }
    }

    /// Read the next token as a type that implements FromStr
    pub fn next<T: str::FromStr>(&mut self) -> T {
        // Skip whitespace
        while self.pos < self.buf.len()
            && (self.buf[self.pos] == b' '
                || self.buf[self.pos] == b'\n'
                || self.buf[self.pos] == b'\r'
                || self.buf[self.pos] == b'\t')
        {
            self.pos += 1;
        }
        // Collect the start
        let start = self.pos;
        // Find end of token
        while self.pos < self.buf.len()
            && !(self.buf[self.pos] == b' '
                || self.buf[self.pos] == b'\n'
                || self.buf[self.pos] == b'\r'
                || self.buf[self.pos] == b'\t')
        {
            self.pos += 1;
        }
        // Convert slice to string
        let token = &self.buf[start..self.pos];
        let s = unsafe { str::from_utf8_unchecked(token) };
        s.parse::<T>().ok().expect("Failed parse")
    }
}

fn main() {
    let mut reader = FastReader::new();

    let n: usize = reader.next();
    let q: usize = reader.next();

    let mut a = vec![0; n];

    let mut ans = 0;

    let f = |a: &Vec<i32>, v: usize| -> i32 {
        let mut res = 0;
        if v >= 1 {
            if a[v] != a[v - 1] {
                res += 1;
            }
        } else {
            if a[v] == 1 {
                res += 1;
            }
        }
        if v + 1 < n {
            if a[v] != a[v + 1] {
                res += 1;
            }
        } else {
            if a[v] == 1 {
                res += 1;
            }
        }
        return res;
    };

    for _ in 0..q {
        let p: usize = reader.next::<usize>() - 1_usize;

        ans -= f(&a, p);
        a[p] = 1 - a[p];
        ans += f(&a, p);

        println!("{}", ans >> 1);
    }
}
