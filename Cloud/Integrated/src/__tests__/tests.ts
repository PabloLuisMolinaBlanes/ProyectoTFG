import {describe, expect, test} from '@jest/globals';
import { comparePasswords } from '../password'; 

test('Password should equal its hash', async () => {
  expect(await comparePasswords("test", "$2a$10$LSxhFhbPYofMQORtPRAws.SrzcmtWMBQjVxctuNLu3bsIQDZdE9oe")).toBe(true);
});