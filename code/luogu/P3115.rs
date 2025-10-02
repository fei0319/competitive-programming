use std::{
    cmp::{max, Reverse},
    collections::BinaryHeap,
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

struct Flight {
    route: Vec<usize>,
    cost: i64,
}

fn main() {
    let mut reader = Reader::new();

    let src: usize = reader.next();
    let snk: usize = reader.next();
    let m = reader.next();

    let mut f = Vec::with_capacity(m);
    for _ in 0..m {
        let cost = reader.next();
        let len = reader.next();
        let mut route = Vec::with_capacity(len);
        for _ in 0..len {
            route.push(reader.next());
        }
        f.push(Flight { route, cost });
    }

    let n = {
        let mut max_id = 0;
        for flight in f.iter() {
            max_id = max(max_id, *flight.route.iter().max().unwrap());
        }
        max_id + 1
    };

    let mut adj = vec![vec![]; n];
    for flight in f.iter() {
        let fid = adj.len();
        adj.resize(adj.len() + flight.route.len(), Vec::new());
        for i in 1..flight.route.len() {
            adj[fid + i - 1].push((fid + i, 0));
        }
        for (i, &x) in flight.route.iter().enumerate() {
            adj[x].push((fid + i, 0));
            adj[fid + i].push((x, flight.cost));
        }
    }

    let mut q = BinaryHeap::new();
    let mut vis = vec![false; adj.len()];
    let mut dis = vec![(i64::MAX, usize::MAX); adj.len()];
    q.push((Reverse((0, 0)), src));
    dis[src] = (0, 0);
    while !q.is_empty() {
        let (_, x) = q.pop().unwrap();
        if vis[x] {
            continue;
        }
        vis[x] = true;
        for &(to, w) in adj[x].iter() {
            let mut next_dis = (dis[x].0 + w, dis[x].1);
            if w > 0 {
                next_dis.1 -= 1;
            } else {
                next_dis.1 += 1;
            }
            if dis[to] > next_dis {
                dis[to] = next_dis;
                q.push((Reverse(dis[to]), to));
            }
        }
    }

    if dis[snk].0 != i64::MAX {
        println!("{} {}", dis[snk].0, dis[snk].1);
    } else {
        println!("-1 -1");
    }
}
