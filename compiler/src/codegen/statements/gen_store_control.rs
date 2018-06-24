use ast::ControlField;
use codegen::{controls, NodeContext};
use inkwell::values::PointerValue;
use inkwell::AddressSpace;

pub fn gen_store_control_statement(
    control: usize,
    field: &ControlField,
    value: usize,
    node: &mut NodeContext,
) -> PointerValue {
    let layout_index = node.layout.control_index(control);
    let control_data = node.get_data_entry(layout_index);
    let control_group = node.get_group_entry(layout_index);

    let store_val = node.get_statement(value);
    controls::build_field_set(
        node.ctx.module,
        node.ctx.b,
        *field,
        control_group,
        control_data,
        store_val,
    );

    // storing a control has no result, return an undefined value
    node.ctx
        .context
        .i8_type()
        .ptr_type(AddressSpace::Generic)
        .get_undef()
}
