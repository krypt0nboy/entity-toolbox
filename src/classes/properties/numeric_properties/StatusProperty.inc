<?php

/**
 * Class StatusProperty
 */
class StatusProperty extends BooleanProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'                => 'status',
        'default_name'                => 'status',
        'default_label'               => 'Status',
        'default_description'         => 'The %toolbox_info_labels_single_lowercase% status.',
        'default_key'                 => 'status',
        'default_schemas_fields_name' => array(
          'base'     => 'status',
          'revision' => 'status',
        ),
        'default_schemas_fields'      => array(
          'base'     => array(
            'description' => 'The %toolbox_info_entity_type% status.',
          ),
          'revision' => array(
            'description' => 'The %toolbox_info_entity_type% status revision.',
          ),
        ),
        'default_forms'               => array(
          'edit' => array(
            'widget'   => 'checkbox',
            'required' => TRUE,
          ),
        ),
        'default_value'               => array(
          'default' => 0,
        ),
        'default_children_inherit'    => TRUE,
        'default_weight'              => 2
      ),
      $args
    );
    parent::__construct($args);
  }
}