/**
 * @param {number} millis
 * @return {Promise}
 */
async function sleep(millis) {
    return new Promise(function (resolve){
        setTimeout(() => resolve(millis), millis);
    })
}
let t = Date.now();
sleep(100).then(() => console.log(Date.now() - t)) // 100

/**
 * let t = Date.now()
 * sleep(100).then(() => console.log(Date.now() - t)) // 100
 */