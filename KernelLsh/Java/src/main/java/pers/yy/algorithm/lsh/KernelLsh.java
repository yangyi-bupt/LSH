package pers.yy.algorithm.lsh;

import org.apache.commons.math3.random.RandomDataGenerator;
import org.apache.mahout.math.SequentialAccessSparseVector;
import org.apache.mahout.math.Vector;

/**
 * Implement Locality-Sensitive Binary Codes from Shift-Invariant Kernels NIPS(2009)
 * http://www.robots.ox.ac.uk/~vgg/rg/papers/binarycodes.pdf
 * cos(w*x + b) + t 
 * 
 * TODO(yiyang): consider to use a run-time gen random method to save space
 *
 * @author Yi Yang (yangyi_bupt@126.com)
 */

public class KernelLsh {
    protected SequentialAccessSparseVector[] projectW;
    protected SequentialAccessSparseVector projectT;
    protected SequentialAccessSparseVector projectB;

    protected int cardinality;
    protected int hashBitNum;

    protected RandomDataGenerator gen = new RandomDataGenerator();
    protected static double pi2 = 2.0 * Math.PI;
    protected double sigmaSquare = -1;
    protected double eps = 0.0001;

    public KernelLsh(int cardinality, int hashBitNum, float sigma) {
        this.cardinality = cardinality;
        this.hashBitNum = hashBitNum;

        projectW = new SequentialAccessSparseVector[hashBitNum];
        projectB = new SequentialAccessSparseVector(hashBitNum);
        projectT = new SequentialAccessSparseVector(hashBitNum);

        RandomDataGenerator gen = new RandomDataGenerator();
        gen.reSeed(1000); // 1000 does not means anything, only to make a fixed sequence

        sigmaSquare = sigma * sigma;
        double tmpGenRes = 0;
        for (int i = 0; i < hashBitNum; ++i) {
            projectT.setQuick(i, gen.nextUniform(-1, 1));
            projectB.setQuick(i, gen.nextUniform(0.0, pi2));
            projectW[i] = new SequentialAccessSparseVector(cardinality);

            for (int j = 0; j < cardinality; ++j) {
                tmpGenRes = gen.nextGaussian(0.0, sigmaSquare);
                // truncate 0
                if (Math.abs(tmpGenRes) > eps) {
                    projectW[i].setQuick(j, tmpGenRes);
                }
            }
        }
    }
    
    public long GetHashValue(final Vector feat) {
        double sum = 0;
        long hash_value = 0;
        // TODO(yiyang): use matrix operations
        for (int i = 0; i < hashBitNum; ++i) {
            sum = feat.dot(projectW[i]) + projectB.get(i);
            if (Math.signum(Math.cos(sum) + projectT.get(i)) >= 0) {
                hash_value |= (long) 1 << i;
            }
        }                                                                                               
        return hash_value;
    }
}
