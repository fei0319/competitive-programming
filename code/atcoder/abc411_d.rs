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

#[derive(Clone)]
struct Node {
    fid: usize,
    s: String,
}

fn main() {
    let mut reader = FastReader::new();

    let n: usize = reader.next();
    let q: usize = reader.next();

    let mut x = vec![Node {
        fid: 0,
        s: "".to_string(),
    }];
    let mut pid = vec![0 as usize; n + 1];

    for _ in 0..q {
        let opt_type: i32 = reader.next();
        let p: usize = reader.next();
        match opt_type {
            1 => {
                pid[p] = pid[0];
            }
            2 => {
                let s: String = reader.next();
                let nid = x.len();
                x.push(Node { fid: pid[p], s });
                pid[p] = nid;
            }
            3 => {
                pid[0] = pid[p];
            }
            _ => panic!(),
        };
    }

    fn get_str(id: usize, x: &Vec<Node>) -> String {
        if id == 0 {
            return "".into();
        }
        return get_str(x[id].fid, x) + &x[id].s;
    }

    println!("{}", get_str(pid[0], &x));
}
