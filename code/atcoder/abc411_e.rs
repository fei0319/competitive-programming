use modint::{Mod998244353, StaticModint};
use tayu_procon::{iolib, modint};
type MInt = StaticModint<Mod998244353>;

fn main() {
    let reader = iolib::get_stdin_source();

    let n: usize = reader.read();

    let mut a = vec![[0; 6]; n];
    let mut vals = Vec::<i32>::new();
    for i in a.iter_mut() {
        for j in i.iter_mut() {
            *j = reader.read();
            vals.push(*j);
        }
    }

    vals.sort();
    vals.dedup();

    let mut b = vec![Vec::<usize>::new(); vals.len()];
    for (i, items) in a.iter().enumerate() {
        for x in items.iter() {
            let idx = vals.binary_search(x).unwrap();
            b[idx].push(i);
        }
    }

    let mut ans = MInt::zero();

    let mut c = vec![6; n];
    let mut p = MInt::one();
    for (i, val) in vals.iter().enumerate().rev() {
        let mut next_p = p;
        for &j in b[i].iter() {
            next_p /= c[j].into();
            c[j] -= 1;
            next_p *= c[j].into();
            if next_p == 0.into() {
                break;
            }
        }

        ans += (p - next_p) * (*val).into();
        p = next_p;
        if next_p == 0.into() {
            break;
        }
    }

    println!("{}", ans);
}
