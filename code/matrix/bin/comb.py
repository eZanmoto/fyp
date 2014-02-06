# Defines the combs function.

def _inc(xs, limits):
    """
    Return the overflow resulting from incrementing `xs` while imposing
    `limits` on each value of `xs`.
    """
    i = 0
    carry = True
    while carry and i < len(xs):
        xs[i] = (xs[i] + 1) % limits[i]
        carry = xs[i] == 0
        i += 1
    return carry


def combs(feats):
    """
    Return an iterator which returns unique lists using the lists in `feats`.
    """
    indices = [0] * len(feats)
    limits = map(len, feats)
    overflow = False
    while not overflow:
        yield [feats[i][indices[i]] for i in xrange(len(feats))]
        overflow = _inc(indices, limits)


if __name__ == '__main__':
    for xs in combs([range(2), range(3), range(4) ]):
        print xs
