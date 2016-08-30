<?php

/**
 * Class PropertyValueBuilder
 */
class EntityToolboxInfoPropertyBuilder extends EntityToolboxInfoPropertyDependentKeyBuilder {

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'model_class'          => 'EntityToolboxInfoPropertyModel',
        'key_builders_classes' => array(
          'callbacks'           => 'EntityToolboxInfoPropertyCallbacksBuilder',
          'schemas_fields_name' => 'EntityToolboxInfoPropertySchemasFieldsNameBuilder',
          'schemas_fields'      => 'EntityToolboxInfoPropertySchemasFieldsBuilder',
          'value'               => 'EntityToolboxInfoPropertyValueBuilder',
          'forms'               => 'EntityToolboxInfoPropertyFormsBuilder',
          'tables'              => 'EntityToolboxInfoPropertyTablesBuilder',
        )
      ),
      $args
    );
    parent::__construct($args);
  }

  public function build() {
    $return = parent::build();

    return $return;
  }

  protected function preSetModelClass() {
    $this->__set('property_instance', $this->constructArgs['property_instance']);
  }

  protected function postSetPropertyInstance() {
    parent::postSetPropertyInstance();
    if (!empty($this->getHookBuilder()
                    ->getRawProperties($this->propertyName))
    ) {
      if (!empty($this->getHookBuilder()
                      ->getRawProperties($this->propertyName)['reference'])
      ) {
        $reference = $this->getHookBuilder()
                          ->getRawProperties($this->propertyName)['reference'];
        if (!is_null($reference) && (!preg_match('/%\w+%/', $reference))) {
          $this->__set('property_reference', $reference);
        }
      }
      else {
        $reference = $this->getPropertyInstance()->getDefaultReference();
        if (($reference != '') && !is_null($reference) && (!preg_match('/%\w+%/', $reference))) {
          $this->__set('property_reference', $reference);
        }
      }
    }
    else {
      $reference = $this->getPropertyInstance()->getDefaultReference();
      if (($reference != '') && !is_null($reference) && (!preg_match('/%\w+%/', $reference))) {
        $this->__set('property_reference', $reference);
      }
    }
  }

  protected function postSetPropertyReference() {
    if (!empty($this->propertyReference) != $this->entityType) {
      $this->__set('property_reference_info', entity_get_info($this->propertyReference));
    }
  }

  protected function postSetPropertyReferenceInfo() {
    $flattened = $this->extractTemplateVars($this->propertyReferenceInfo, '', 'property_reference_info_');
    foreach ($flattened as $name => $value) {
      $this->updateTemplateVars($name, $value);
    }
  }

  /**
   * @param       $keyBuilderClass
   * @param array $args
   *
   * @return mixed
   */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'property_type'      => $this->constructArgs['property_type'],
      'property_instance'  => $this->constructArgs['property_instance'],
      'property_reference' => $this->propertyReference,
    ), $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }

  /**
   * Builds the value "type".
   */
  protected function buildType() {
//    return $this->propertyInstance->getDefaultType();
  }

  /**
   * Builds the value "php type".
   */
  protected function buildPhpType() {
//    return $this->propertyInstance->getDefaultPhpType();
  }

  /**
   * Builds the value "drupal type".
   */
  protected function buildDrupalType() {
    $defaultBuild    = $this->buildKeyDefault('drupal type');
    $defaultMultiple = $this->getPropertyInstance()->getDefaultMultiple();
    $rawProperty     = $this->getHookBuilder()
                            ->getRawProperties($this->propertyName);
    $rawMultiple     = !empty($rawProperty['multiple']) ? $rawProperty['multiple'] : NULL;
    $multiple        = isset($rawMultiple) ? $rawMultiple : $defaultMultiple;
    if ($multiple) {
      return preg_match('/list<\w+>/', $defaultBuild) ? $defaultBuild : "list<$defaultBuild>";
    }
    else {
      $rebuild = preg_match('/list<(?P<type>.+)>/', $defaultBuild, $matches) ? $matches['type'] : $defaultBuild;

      return $rebuild;
    }
  }

  /**
   * Builds the value "reference".
   */
  protected function buildReference() {
  }

  /**
   * Builds the value "key".
   */
  protected function buildPropertyKey() {
  }

  /**
   * Builds the value "has_revisions".
   */
  protected function buildHasRevisions() {
  }

  /**
   * Builds the value "has_translations".
   */
  protected function buildHasTranslations() {
    $entity_type_has_translations = $this->getHookBuilder()
                                         ->getBuild('has_translations');
    if ($entity_type_has_translations) {
      $return = $this->buildKeyDefault('has_translations');

      return $return;
    }
    else {
      return FALSE;
    }
  }

  /**
   * Builds the value "multiple".
   */
  protected function buildMultiple() {
  }

  /**
   * Builds the value "serialize".
   */
  protected function buildSerialize() {
  }

  /**
   * Builds the value "label".
   */
  protected function buildLabel() {
  }

  /**
   * Builds the value "description".
   */
  protected function buildDescription() {
  }

  /**
   * Builds the value "required".
   */
  protected function buildRequired() {
  }

  /**
   * Builds the value "forms".
   */
  protected function buildForms() {
    return $this->getKeyBuilder('forms')->build();
  }

  /**
   * Builds the value "is_unique".
   */
  protected function buildIsUnique() {
    return $this->getPropertyInstance()->getDefaultIsUnique();
  }

  /**
   * Builds the value "tables".
   */
  protected function buildTables() {
    $defaultMultiple = $this->getPropertyInstance()->getDefaultMultiple();
    $rawProperty     = $this->getHookBuilder()
                            ->getRawProperties($this->propertyName);
    $rawMultiple     = !empty($rawProperty['multiple']) ? $rawProperty['multiple'] : FALSE;
    if ($rawMultiple) {
      return $this->getKeyBuilder('tables')->build();
    }
    else {
      if ($defaultMultiple) {
        return $this->getKeyBuilder('tables')->build();
      }
      else {
        return array();
      }
    }

  }

  /**
   * Builds the value "schemas_fields".
   */
  protected function buildSchemasFields() {
    return $this->getKeyBuilder('schemas_fields')->build();
  }

  /**
   * Builds the value "schemas_fields_name".
   */
  protected function buildSchemasFieldsName() {
    return $this->getKeyBuilder('schemas_fields_name')->build();
  }

  protected function validateSchemasFieldsName($preValidatedBuild) {
    return $preValidatedBuild;
  }

  /**
   * Builds the value "value".
   */
  protected function buildValue() {
    return $this->getKeyBuilder('value')->build();
  }

  /**
   * Builds the value "callbacks".
   */
  protected function buildCallbacks() {
    return $this->getKeyBuilder('callbacks')->build();
  }

  /**
   * Builds the value "views expose".
   */
  protected function buildViewsExpose() {
  }

  /**
   * Builds the value "weight".
   */
  protected function buildWeight() {
  }
}