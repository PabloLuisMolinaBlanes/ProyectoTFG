import {describe, expect, test} from '@jest/globals';
import { generateRandomString, verifyNIFLetter } from '../utils';

test('Generated password should always have parameter length length', async () => {
  expect(generateRandomString(10).length).toBe(10);
});

test('Number without letter should fail', async () => {
  expect(verifyNIFLetter("12345678", false)).toBe(false);
});

test('Foreign document without letter should fail', async () => {
  expect(verifyNIFLetter("12345678R", true)).toBe(false);
});

test('Incorrect number should return false', async () => {
  expect(verifyNIFLetter("12345678R", false)).toBe(false);
});

test('Correct number should return true', async () => {
  expect(verifyNIFLetter("12345678Z", false)).toBe(true);
});

test('Incorrect foreign number should return false', async () => {
  expect(verifyNIFLetter("X2345678R", true)).toBe(false);
});

test('Correct foreign number should return true', async () => {
  expect(verifyNIFLetter("X2345678T", true)).toBe(true);
});