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
    let p: String = reader.next();
    let l: usize = reader.next();

    println!("{}", if p.len() >= l { "Yes" } else { "No" });
}
