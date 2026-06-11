import {describe, expect, test, vi} from 'vitest';
import {createTest} from '../crud'
import prismaMock from '../__mocks__/db'

vi.mock('../db')

test('Sanity test of mock', async () => {
  prismaMock.profile.findFirst.mockResolvedValue(null);
  await expect(prismaMock.profile.findFirst({})).resolves.toBeNull()
})

test('If findProfile returns null, then "Wrong Password" is returned', async () => {
  prismaMock.profile.findFirst.mockResolvedValue(null);
 await expect(createTest("null", "null", "null", "null", "null", "null")).resolves.toStrictEqual({error: "Wrong password"})
})