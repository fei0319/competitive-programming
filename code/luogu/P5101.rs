use std::{
    cmp::max,
    io::{self},
};

pub struct Reader {
    buffer: Vec<String>,
}

impl Reader {
    pub fn new() -> Self {
        Self { buffer: Vec::new() }
    }
    pub fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed to parse token");
            }
            let mut input = String::new();
            io::stdin()
                .read_line(&mut input)
                .expect("Failed to read line");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

struct Counter {
    cnt: Vec<usize>,
    buf: Vec<Vec<usize>>,
}
impl Counter {
    pub fn new(n: usize) -> Self {
        let mut res = Self {
            cnt: vec![0; n],
            buf: vec![Vec::new()],
        };
        for i in 0..n {
            res.buf[0].push(i);
        }
        res
    }
    pub fn add(&mut self, x: usize) {
        self.cnt[x] += 1;
        if self.buf.len() <= self.cnt[x] {
            self.buf.push(Vec::new());
        }
        self.buf[self.cnt[x]].push(x);
    }
    pub fn del(&mut self, x: usize) {
        self.cnt[x] -= 1;
        self.buf[self.cnt[x]].push(x);
    }
    pub fn max_occurence(&mut self) -> usize {
        loop {
            let buf_len = self.buf.len();
            let last_buf = self.buf.last_mut().unwrap();
            while !last_buf.is_empty() && self.cnt[*last_buf.last().unwrap()] != buf_len - 1 {
                last_buf.pop();
            }
            if last_buf.is_empty() {
                self.buf.pop();
            } else {
                break;
            }
        }
        self.buf.len() - 1
    }
}

fn main() {
    let mut reader = Reader::new();

    let n = reader.next();
    let m = reader.next();
    let mut c = vec![0_usize; n];
    for i in c.iter_mut() {
        *i = reader.next::<usize>() - 1;
    }

    let mut counter = Counter::new(m);
    for color in c.iter() {
        counter.add(*color);
    }

    let mut ans = vec![0_usize; m];
    for b in 0..2 {
        let mut pairs_of_color = vec![vec![]; m];

        let mut i = b + 1;
        while i < n {
            let pair = [c[i - 1], c[i]];
            pairs_of_color[pair[0]].push(pair);
            if pair[1] != pair[0] {
                pairs_of_color[pair[1]].push(pair);
            }
            i += 2;
        }

        for color in 0..m {
            let pairs = &pairs_of_color[color];
            let mut res = 0;
            if b == 1 && c[0] == color {
                res += 1;
                counter.del(color);
            }
            if n % 2 != b && c[n - 1] == color {
                res += 1;
                counter.del(color);
            }
            for pair in pairs {
                pair.iter().for_each(|&x| {
                    if x == color {
                        res += 1;
                    }
                    counter.del(x);
                });
            }
            ans[color] = max(ans[color], res + counter.max_occurence());
            for pair in pairs {
                pair.iter().for_each(|&x| {
                    if x == color {
                        res -= 1;
                    }
                    counter.add(x);
                });
            }
            for _ in 0..res {
                counter.add(color);
            }
        }
    }

    for color in 0..m {
        println!("{}", n - ans[color]);
    }
}
