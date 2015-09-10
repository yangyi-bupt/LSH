package pers.yy.algorithm.lsh;

import org.apache.mahout.math.SequentialAccessSparseVector;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

/**
 * @author Yi Yang (yangyi_bupt@126.com)
 */

public class KernelLshTest {
    protected KernelLsh lshLowPrecision, lshHighPrecision;
    protected int cardinality = 30000;
    protected SequentialAccessSparseVector featVec1 = new SequentialAccessSparseVector(cardinality);
    protected SequentialAccessSparseVector featVec2 = new SequentialAccessSparseVector(cardinality);

    @Before
    public void setUp() throws Exception {
        lshLowPrecision = new KernelLsh(cardinality, 64, 0.1f);
        lshHighPrecision = new KernelLsh(cardinality, 64, 3.f);
        
        featVec1.set(0, 1.0);
        featVec1.set(cardinality / 4, 1.0);
        featVec1.set(cardinality / 3, 1.0);
        featVec1.set(cardinality / 2, 1.0);
        featVec1.set(cardinality - 1, 1.0);
        
        featVec2.assign(featVec1);
        featVec2.set(cardinality - 2, 1.0);
    }

    @Test
    public void testGetHashValue() {
        String hashLowLsh1 = String.format("%016x", lshLowPrecision.GetHashValue(featVec1));
        String hashLowLsh2 = String.format("%016x", lshLowPrecision.GetHashValue(featVec2));
        Assert.assertEquals(hashLowLsh1, hashLowLsh2);
        
        String hashHighLsh1 = String.format("%016x", lshHighPrecision.GetHashValue(featVec1));
        String hashHighLsh2 = String.format("%016x", lshHighPrecision.GetHashValue(featVec2));
        Assert.assertFalse(hashHighLsh1.equals(hashHighLsh2));
    }
}
