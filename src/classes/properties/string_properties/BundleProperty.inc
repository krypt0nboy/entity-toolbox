<?php

/**
 * Class BundleProperty
 */
class BundleProperty extends MachineNameProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'                => 'bundle',
        'default_drupal_type'         => 'token',
        'default_name'                => 'type',
        'default_key'                 => 'bundle',
        'default_label'               => 'Type',
        'default_required'            => TRUE,
        'default_description'         => 'The %toolbox_info_labels_single_lowercase% type.',
        'default_schemas_fields_name' => array(
          'base'     => 'type',
          'revision' => 'type',
        ),
        'default_schemas_fields'      => array(
          'base'     => array(
            'description' => 'The {%toolbox_info_bundle_entity%}.type of this %toolbox_info_entity_type%.',
          ),
          'revision' => array(
            'description' => '',
          ),
        ),
        'default_forms'               => array(
          'edit'   => array(
            'expose' => FALSE,
          ),
          'inline' => array(
            'expose' => FALSE,
          ),
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}