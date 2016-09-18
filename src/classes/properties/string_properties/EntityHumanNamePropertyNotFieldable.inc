<?php

/**
 * Class EntityHumanNamePropertyNotFieldable
 */
class EntityHumanNamePropertyNotFieldable extends EntityHumanNameProperty {
  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = array_replace_recursive(
      array(
        'default_type'                => 'entity_human_name',
        'default_name'                => 'label',
        'default_key'                 => 'label',
        'default_has_translations'    => FALSE,
        'default_has_revisions'       => FALSE,
        'default_label'               => 'Label',
        'default_description'         => 'The human-readable name of this %toolbox_info_labels_single_lowercase% type.',
        'default_schemas_fields_name' => array(
          'base'              => 'label',
          'revision'          => 'label',
          'relation'          => 'label',
          'relation_revision' => 'label',
        ),
        'default_schemas_fields'      => array(
          'base' => array(
            'description' => 'The human-readable name of this %toolbox_info_bundle_of% type.'
          ),
        ),
        'default_forms'               => array(
          'edit'  => array(
            'required' => TRUE
          ),
          'clone' => array(
            'required' => TRUE
          )
        ),
        'default_value'               => array(
          'max_length' => 32
        ),
      ),
      $args
    );
    parent::__construct($args);
  }
}