<?php

/**
 * Class EntityMachineNameProperty
 */
class EntityMachineNameProperty extends MachineNameProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'                => 'entity_machine_name',
        'default_description'         => 'A unique machine-readable name for this %toolbox_info_labels_single_lowercase%. It must only contain lowercase letters, numbers, and underscores.',
        'default_name'                => 'type',
        'default_key'                 => 'name',
        'default_schemas_fields_name' => array(
          'base'              => 'type',
          'revision'          => 'type',
          'relation'          => 'type',
          'relation_revision' => 'type',
        ),
        'default_schemas_fields'      => array(
          'base' => array(
            'description' => 'he machine-readable name of this %toolbox_info_bundle_of% type.',
            'length'      => 32,
          ),
        ),
        'default_callbacks'           => array(
          'options_list' => '%toolbox_info_entity_type%_get_types',
        ),
        'default_forms'               => array(
          'edit'   => array(
            'source' => '',
          ),
          'inline' => array(
            'source' => '',
          ),
        ),
        'default_value'               => array(
          'max length' => 32
        ),
        'default_is_unique'           => TRUE,
        'default_weight'              => -997
      ),
      $args
    );
    parent::__construct($args);
  }
}