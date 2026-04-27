import {describe, expect, test} from '@jest/globals';
import { comparePasswords, hashPassword } from '../password'; 

test('Cleartext password should compare to its hash', async () => {
  expect(await comparePasswords("test", "$2a$10$LSxhFhbPYofMQORtPRAws.SrzcmtWMBQjVxctuNLu3bsIQDZdE9oe")).toBe(true);
});

test('Cleartext password should compare to itself hash', async () => {
  // Arrange
  const passwordHash = await hashPassword("test");
  // Assert
  expect(await comparePasswords("test", passwordHash)).toBe(true);
});