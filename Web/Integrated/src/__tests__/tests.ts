import {describe, expect, test} from '@jest/globals';
import { generateRandomString, verifyNIFLetter } from '../utils';

test('Generated password should always have parameter length length', async () => {
  expect(generateRandomString(10).length).toBe(10);
});