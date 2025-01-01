use neon::prelude::*;

fn getxattr(mut cx: FunctionContext) -> JsResult<JsString> {
    if cx.len() < 2 {
        return cx.throw_type_error("expected 2 arguments");
    }
    let path = cx.argument::<JsString>(0)?.value(&mut cx);
    let name = cx.argument::<JsString>(1)?.value(&mut cx);

    match xattr::get(&path, &name) {
        Ok(value) => {
            if let Some(value) = value {
                let str_value = String::from_utf8(value);
                if let Ok(str_value) = str_value {
                    Ok(cx.string(&str_value))
                } else {
                    cx.throw_error("failed to convert value to string")
                }
            } else {
                Ok(cx.string(""))
            }
        }
        Err(e) => cx.throw_error(e.to_string()),
    }
}

#[neon::main]
fn main(mut cx: ModuleContext) -> NeonResult<()> {
    cx.export_function("getxattr", getxattr)?;
    Ok(())
}
